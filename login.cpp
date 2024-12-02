#include "login.h"
#include "qboxlayout.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
#include <QProcess>
#include <QRandomGenerator>
#include <QTimer>

QTimer *verificationTimer = nullptr;
int remainingAttempts = 3;
bool isTimerExpired = false;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("PHARMEASE - Login");


    // Initialize UI states
    ui->stackedWidget->setCurrentWidget(ui->login);
    ui->passwordlogin->setEchoMode(QLineEdit::Password);
    ui->registerpass->setEchoMode(QLineEdit::Password);
    ui->forgetuser_3->setEchoMode(QLineEdit::Password);
    ui->forgetuser_2->setEnabled(false);
    ui->forgetuser_3->setEnabled(false);

    // Connect UI actions to slots
    connect(ui->oklogin, &QPushButton::clicked, this, &Login::on_oklogin_clicked);
    connect(ui->gotoregister, &QPushButton::clicked, this, &Login::on_gotoregister_clicked);
    connect(ui->ok, &QPushButton::clicked, this, &Login::on_okregister_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &Login::on_cancel_clicked);
    connect(ui->cancel_2, &QPushButton::clicked, this, &Login::on_cancelForget_clicked);
    connect(ui->forget, &QPushButton::clicked, this, &Login::on_forget_clicked);
    connect(ui->cancellogin, &QPushButton::clicked, this, &Login::exitApplication);
    connect(ui->ok_email, &QPushButton::clicked, this, &Login::on_okEmail_clicked);
    connect(ui->ok_verificationcode, &QPushButton::clicked, this, &Login::on_okVerificationCode_clicked);
    connect(ui->ok_newpassword, &QPushButton::clicked, this, &Login::on_okNewPassword_clicked);
    connect(ui->arduinologin, &QPushButton::clicked, this, &Login::on_arduinoLogin_clicked);
    // Show/hide password toggle
    connect(ui->showpassword, &QCheckBox::toggled, this, &Login::on_showpassword_toggled);
    connect(ui->showpassword_2, &QCheckBox::toggled, this, [this](bool checked) {
        ui->forgetuser_3->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    });
}

Login::~Login()
{
    delete ui;
}
void Login::on_gotoregister_clicked()
{
    // Switch to the register page
    ui->stackedWidget->setCurrentWidget(ui->register_2);  // Assuming "register_2" is the name of the registration widget
    this->setWindowTitle("PHARMEASE - Register");         // Update the window title to reflect the current page
}
// Handle login
void Login::on_oklogin_clicked()
{
    QString cin = ui->userlogin->text();
    QString password = ui->passwordlogin->text();

    // Authenticate user and fetch role
    QSqlQuery query;
    QString hashedPassword = hashPassword(password);
    query.prepare("SELECT ROLE FROM EMPLOYEE WHERE CINEMP = :cin AND PASSWORD = :password");
    query.bindValue(":cin", cin);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        userRole = query.value("ROLE").toString();  // Save the role
        qDebug() << "User role fetched in Login dialog:" << userRole;

        this->accept();  // Close the Login dialog with accepted state
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials. Please try again.");
    }
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

// Cancel and return to login page from forget or register page
void Login::on_cancelForget_clicked()
{
    // Reset all variables and states
    remainingAttempts = 3;
    isTimerExpired = false;

    if (verificationTimer) {
        verificationTimer->stop();
        delete verificationTimer;
        verificationTimer = nullptr;
    }

    // Reset all UI elements
    ui->forgetuser->clear();       // Clear email input
    ui->forgetuser_2->clear();     // Clear verification code input
    ui->forgetuser_3->clear();     // Clear new password input

    ui->forgetuser_2->setEnabled(false);  // Disable verification code input
    ui->forgetuser_3->setEnabled(false);  // Disable new password input
    ui->countdownLabel->setVisible(false);  // Hide the countdown label

    // Navigate back to the login page
    ui->stackedWidget->setCurrentWidget(ui->login);
    this->setWindowTitle("PHARMEASE - Login");
}


void Login::on_cancel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login);
    this->setWindowTitle("PHARMEASE - Login");
}

// Forget password page
void Login::on_forget_clicked()
{
    // Reset all variables and states
    remainingAttempts = 3;
    isTimerExpired = false;

    if (verificationTimer) {
        verificationTimer->stop();
        delete verificationTimer;
        verificationTimer = nullptr;
    }

    // Reset all UI elements
    ui->forgetuser->clear();       // Clear email input
    ui->forgetuser_2->clear();     // Clear verification code input
    ui->forgetuser_3->clear();     // Clear new password input

    ui->forgetuser_2->setEnabled(false);  // Disable verification code input
    ui->forgetuser_3->setEnabled(false);  // Disable new password input
    ui->countdownLabel->setVisible(false);  // Hide the countdown label

    // Navigate to the forget password page
    ui->stackedWidget->setCurrentWidget(ui->forget_2);
    this->setWindowTitle("PHARMEASE - Forget Password");
}


// Send verification code via email
void Login::on_okEmail_clicked()
{
    QString email = ui->forgetuser->text();

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Error", "Email cannot be empty.");
        return;
    }

    // Check if the email exists in the database
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE EMAIL = :email");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        if (query.value(0).toInt() == 0) {
            QMessageBox::warning(this, "Error", "No account associated with this email.");
            return;
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to query database. Please try again.");
        return;
    }

    // Generate a random 4-digit verification code
    verificationCode = QString::number(QRandomGenerator::global()->bounded(1000, 9999));

    QProcess *process = new QProcess(this);
    QString pythonPath = "python";
    QString scriptPath = "E:/2A/projetcpp-smart-pharmacy-2a30/send_email.py";

    QStringList arguments;
    arguments << scriptPath << email << "Your verification code is: " + verificationCode;

    process->start(pythonPath, arguments);

    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus) {
        if (exitCode == 0) {
            QMessageBox::information(this, "Success", "Verification code sent to your email.");
            ui->forgetuser_2->setEnabled(true);
            startVerificationTimer();  // Start the 60-second timer
            remainingAttempts = 3;     // Reset attempts
            isTimerExpired = false;    // Reset the timer status
        } else {
            QMessageBox::warning(this, "Error", "Failed to send email. Check your setup.");
        }
        process->deleteLater();
    });
}

void Login::startVerificationTimer()
{
    if (verificationTimer) {
        verificationTimer->stop();
        delete verificationTimer;
    }

    // Reset state variables
    isTimerExpired = false;
    int countdown = 60;  // Countdown starts from 60 seconds

    // Update the countdown label initially
    ui->countdownLabel->setText(QString("Time remaining: %1 seconds").arg(countdown));
    ui->countdownLabel->setVisible(true);  // Ensure the label is visible

    // Create the timer for the countdown
    verificationTimer = new QTimer(this);

    // Connect to a lambda function to update the label every second
    connect(verificationTimer, &QTimer::timeout, [=]() mutable {
        countdown--;

        if (countdown > 0) {
            // Update the label with the remaining time
            ui->countdownLabel->setText(QString("Time remaining: %1 seconds").arg(countdown));
        } else {
            // Time expired, disable input and show a warning
            isTimerExpired = true;
            ui->forgetuser_2->setEnabled(false);
            ui->countdownLabel->setText("Time expired.");
            verificationTimer->stop();
        }
    });

    // Start the timer to tick every second
    verificationTimer->start(1000);
}


void Login::on_okVerificationCode_clicked()
{
    if (isTimerExpired) {
        QMessageBox::warning(this, "Error", "Time expired. Please request a new verification code.");
        return;
    }

    QString enteredCode = ui->forgetuser_2->text().trimmed();

    if (enteredCode.isEmpty()) {
        QMessageBox::warning(this, "Invalid Code", "Verification code cannot be empty.");
        return;
    }

    if (enteredCode == verificationCode) {
        QMessageBox::information(this, "Verified", "Verification code valid. Set your new password.");
        ui->forgetuser_3->setEnabled(true);
        if (verificationTimer) verificationTimer->stop();  // Stop the timer
        ui->countdownLabel->setVisible(false);  // Hide the timer label
    } else {
        remainingAttempts--;
        if (remainingAttempts > 0) {
            QMessageBox::warning(this, "Invalid Code", QString("Incorrect code. %1 attempts remaining.").arg(remainingAttempts));
        } else {
            QMessageBox::warning(this, "Invalid Code", "Maximum attempts reached. Please request a new verification code.");
            ui->forgetuser_2->setEnabled(false);
            if (verificationTimer) verificationTimer->stop();  // Stop the timer
            ui->countdownLabel->setVisible(false);  // Hide the timer label
        }
    }
}
void Login::on_okNewPassword_clicked()
{
    QString newPassword = ui->forgetuser_3->text();
    QString email = ui->forgetuser->text();

    if (newPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "New password cannot be empty.");
        return;
    }

    QString hashedPassword = hashPassword(newPassword);
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET PASSWORD = :password WHERE EMAIL = :email");
    query.bindValue(":password", hashedPassword);
    query.bindValue(":email", email);

    if (query.exec()) {
        // Fetch full name and CIN from the database
        QString fullName, cin;
        QSqlQuery userQuery;
        userQuery.prepare("SELECT FULL_NAME, CINEMP FROM EMPLOYEE WHERE EMAIL = :email");
        userQuery.bindValue(":email", email);

        if (userQuery.exec() && userQuery.next()) {
            fullName = userQuery.value("FULL_NAME").toString();
            cin = userQuery.value("CINEMP").toString();
        } else {
            QMessageBox::warning(this, "Error", "Failed to fetch user details.");
            return;
        }

        QMessageBox::information(this, "Success", "Password updated successfully.");
        ui->stackedWidget->setCurrentWidget(ui->login);

        // Trigger the Python script to notify the admin
        QProcess *process = new QProcess(this);
        QString pythonPath = "python";  // Adjust this if your Python executable has a different path
        QString scriptPath = "E:/2A/projetcpp-smart-pharmacy-2a30/send_password_update_notification.py";

        QStringList arguments;
        arguments << scriptPath
                  << "timoumiaa55@gmail.com"  // Replace with the admin's email
                  << fullName
                  << cin;

        process->start(pythonPath, arguments);

        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus) {
            if (exitCode == 0) {
                qDebug() << "Admin notification email sent successfully.";
            } else {
                qDebug() << "Failed to send admin notification email.";
            }
            process->deleteLater();
        });
    } else {
        QMessageBox::warning(this, "Error", "Failed to update password. Please try again.");
    }
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
    query.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE CINEMP = :cin AND PASSWORD = :password");
    query.bindValue(":cin", cin);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
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

// Exit the application
void Login::exitApplication()
{
    qDebug() << "Exit button clicked. Exiting application...";
    QCoreApplication::exit(0);
}
void Login::on_arduinoLogin_clicked() {
    // Show the "Waiting for Token" dialog
    QDialog *waitingDialog = new QDialog(this);
    waitingDialog->setWindowTitle("Waiting for Token");
    QLabel *label = new QLabel("Please scan your token...", waitingDialog);
    QVBoxLayout *layout = new QVBoxLayout(waitingDialog);
    layout->addWidget(label);
    waitingDialog->setLayout(layout);
    waitingDialog->resize(200, 100);
    waitingDialog->show();

    qDebug() << "Waiting for token scan...";

    // Configure the serial port
    QSerialPort *serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3"); // Adjust to match your Arduino's COM port
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadWrite)) { // Ensure Read/Write mode
        qDebug() << "Failed to open serial port:" << serialPort->errorString();
        QMessageBox::warning(this, "Error", "Failed to connect to Arduino. Please check your setup.");
        waitingDialog->close();
        return;
    }

    // Connect to the serial port's readyRead signal
    connect(serialPort, &QSerialPort::readyRead, [=]() mutable {
        // Append data to the buffer
        buffer.append(QString::fromUtf8(serialPort->readAll()));

        // Check if the buffer contains a complete token (terminated by \n)
        if (buffer.contains("\n")) {
            QString token = buffer.left(buffer.indexOf("\n")).trimmed(); // Extract the token
            buffer.remove(0, buffer.indexOf("\n") + 1); // Remove the processed token from the buffer

            qDebug() << "Scanned token:" << token;

            // Check if the token is valid in the database
            QSqlQuery query;
            query.prepare("SELECT FULL_NAME, ROLE FROM EMPLOYEE WHERE TOKEN_LOGIN = :token");
            query.bindValue(":token", token);

            if (query.exec() && query.next()) {
                // Token is valid, retrieve user full name and role
                QString fullName = query.value("FULL_NAME").toString();
                QString role = query.value("ROLE").toString();
                userRole = role;  // Save the role for further use
                qDebug() << "Token valid. Employee full name:" << fullName;

                // Send the welcome message to Arduino
                QString message = fullName;
                if (serialPort->write(message.toUtf8() + "\n") == -1) {
                    qDebug() << "Failed to send message to Arduino.";
                } else {
                    qDebug() << "Message sent to Arduino: " << message;
                }

                // Close the waiting dialog and proceed with login
                waitingDialog->accept();
                serialPort->close();
                delete serialPort;

                this->accept(); // Close the login dialog with accepted state
            } else {
                // Invalid token
                QMessageBox::warning(this, "Login Failed", "Invalid token. Please try again.");
                qDebug() << "Invalid token.";
            }
        }
    });

    // Add a timeout to close the dialog if no token is scanned
    QTimer::singleShot(10000, [=]() {
        if (waitingDialog->isVisible()) {
            QMessageBox::warning(this, "Timeout", "No token was scanned. Please try again.");
            waitingDialog->close();
            serialPort->close();
            delete serialPort;
        }
    });
}
