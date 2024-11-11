#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
#include <QProcess>
#include <QRandomGenerator>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // Set the stacked widget to start on the login page
    ui->stackedWidget->setCurrentWidget(ui->login);

    // Set password fields to mask input by default
    ui->passwordlogin->setEchoMode(QLineEdit::Password);
    ui->registerpass->setEchoMode(QLineEdit::Password);
    ui->forgetuser_3->setEchoMode(QLineEdit::Password);  // For new password in forget password
    ui->forgetuser_2->setEnabled(false);  // Disable verification code input initially
    ui->forgetuser_3->setEnabled(false);  // Disable new password input initially

    // Connect buttons and widgets
    connect(ui->oklogin, &QPushButton::clicked, this, &Login::on_oklogin_clicked);
    connect(ui->gotoregister, &QPushButton::clicked, this, &Login::on_gotoregister_clicked);
    connect(ui->ok, &QPushButton::clicked, this, &Login::on_okregister_clicked);
    connect(ui->showpassword, &QCheckBox::toggled, this, &Login::on_showpassword_toggled);
    connect(ui->cancel, &QPushButton::clicked, this, &Login::on_cancel_clicked);
    connect(ui->forget, &QPushButton::clicked, this, &Login::on_forget_clicked);
    connect(ui->cancel_2, &QPushButton::clicked, this, &Login::on_cancelForget_clicked);
    connect(ui->cancellogin, &QPushButton::clicked, this, &Login::exitApplication);

    // Forget password connections
    connect(ui->ok_2, &QPushButton::clicked, this, [this]() {
        if (ui->forgetuser_2->isEnabled()) {
            verifyCodeAndEnablePasswordReset();  // If code input is active, verify the code
        } else {
            sendVerificationCode(ui->forgetuser->text());  // Otherwise, send verification code
        }
    });

    connect(ui->showpassword_2, &QCheckBox::toggled, this, [this](bool checked) {
        ui->forgetuser_3->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    });
}

Login::~Login()
{
    delete ui;
}

// Handle login
void Login::on_oklogin_clicked()
{
    QString cin = ui->userlogin->text();
    QString password = ui->passwordlogin->text();

    if (authenticateUser(cin, password)) {
        this->accept();  // Close login dialog with accepted state
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials. Please try again.");
    }
}

// Switch to register page
void Login::on_gotoregister_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->register_2);
}

// Handle registration
void Login::on_okregister_clicked()
{
    QString cin = ui->registeruser->text();
    QString password = ui->registerpass->text();

    if (cin.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "CIN and Password cannot be empty.");
        return;
    }

    if (!isCinExists(cin)) {
        QMessageBox::warning(this, "Registration Failed", "CIN does not exist in the system.");
        return;
    }

    if (isPasswordSet(cin)) {
        QMessageBox::warning(this, "Registration Failed", "You already have an account.");
        return;
    }

    // Hash and store the password
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET PASSWORD = :password WHERE CINEMP = :cin");
    query.bindValue(":password", hashedPassword);
    query.bindValue(":cin", cin);

    if (query.exec()) {
        QMessageBox::information(this, "Registration Successful", "Your account has been created.");
        ui->stackedWidget->setCurrentWidget(ui->login);
    } else {
        QMessageBox::warning(this, "Registration Failed", "Could not register. Please try again.");
    }
}

// Toggle password visibility
void Login::on_showpassword_toggled(bool checked)
{
    ui->passwordlogin->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    ui->registerpass->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void Login::on_cancelForget_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login);  // Switch back to login page
}

// Switch back to login
void Login::on_cancel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login);
}

// Forget password page
void Login::on_forget_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->forget_2);
}

// Send verification code via WhatsApp
void Login::sendVerificationCode(const QString &phone)
{
    if (phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Phone number cannot be empty.");
        return;
    }

    // Generate a random 4-digit verification code
    verificationCode = QString::number(QRandomGenerator::global()->bounded(1000, 9999));

    QProcess *process = new QProcess(this);
    QString pythonPath = "python";  // Ensure Python is in the PATH or specify the full path
    QString scriptPath = "E:/2A/projetcpp-smart-pharmacy-2a30/send_whatsapp.py";

    QStringList arguments;
    arguments << scriptPath << phone << "Your verification code is: " + verificationCode;

    process->start(pythonPath, arguments);

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus) {
        if (exitCode == 0) {
            QMessageBox::information(this, "Success", "Verification code sent.");
            ui->forgetuser_2->setEnabled(true);  // Enable verification code input
        } else {
            QMessageBox::warning(this, "Error", "Failed to send WhatsApp message. Check your setup.");
        }
        process->deleteLater();
    });
}

void Login::verifyCodeAndEnablePasswordReset()
{
    QString enteredCode = ui->forgetuser_2->text().trimmed();  // Ensure there is no trailing whitespace
    if (enteredCode.isEmpty()) {
        QMessageBox::warning(this, "Invalid Code", "Verification code cannot be empty.");
        return;
    }

    if (enteredCode == verificationCode) {
        QMessageBox::information(this, "Verified", "Code correct. Set a new password.");
        ui->forgetuser_3->setEnabled(true);  // Enable new password input
    } else {
        QMessageBox::warning(this, "Invalid Code", "The verification code is incorrect. Please try again.");
    }
}

// Reset password
void Login::resetPassword()
{
    QString newPassword = ui->forgetuser_3->text();
    QString cin = ui->forgetuser->text();  // Assuming forgetuser holds CINEMP from the forget page.

    if (newPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "New password cannot be empty.");
        return;
    }

    QString hashedPassword = hashPassword(newPassword);
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET PASSWORD = :password WHERE CINEMP = :cin");
    query.bindValue(":password", hashedPassword);
    query.bindValue(":cin", cin);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Password updated successfully.");
        ui->stackedWidget->setCurrentWidget(ui->login);  // Return to login page
    } else {
        QMessageBox::warning(this, "Error", "Failed to update password. Please check your input and try again.");
    }
}

// Utility: Check if CIN exists
bool Login::isCinExists(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE CINEMP = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// Utility: Check if password is set for CIN
bool Login::isPasswordSet(const QString &cin)
{
    QSqlQuery query;
    query.prepare("SELECT PASSWORD FROM EMPLOYEE WHERE CINEMP = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return !query.value(0).toString().isEmpty();
    }
    return false;
}

// Utility: Hash password
QString Login::hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

// Utility: Authenticate user
bool Login::authenticateUser(const QString &cin, const QString &password)
{
    QString hashedPassword = hashPassword(password);
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE (CINEMP = :cin) AND PASSWORD = :password");
    query.bindValue(":cin", cin);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
void Login::exitApplication()
{
    qDebug() << "Exit button clicked. Exiting application...";
    QCoreApplication::exit(0);
}
