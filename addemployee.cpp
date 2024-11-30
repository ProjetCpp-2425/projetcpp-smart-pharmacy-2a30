#include "addemployee.h"
#include "ui_addemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QDate>
#include <QDebug>  // For debugging
#include <QFile>
#include <QFileDialog>

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee)
{
    ui->setupUi(this);
    this->setWindowTitle("ADD Employee ;)");
    QRegularExpression cinRegEx("\\d{8}");
    QValidator *cinValidator = new QRegularExpressionValidator(cinRegEx, this);
    ui->cinLineEdit->setValidator(cinValidator);
    ui->phoneLineEdit->setValidator(cinValidator);

    // Regular expression for email validation
    QRegularExpression emailRegEx("[\\w\\.]+@[\\w\\.]+\\.[a-zA-Z]{2,}");
    QValidator *emailValidator = new QRegularExpressionValidator(emailRegEx, this);
    ui->emailLineEdit->setValidator(emailValidator);

    generateEmployeeId();

    connect(ui->okbutton, &QPushButton::clicked, this, &AddEmployee::onOkButtonClicked);
    connect(ui->cancelbutton, &QPushButton::clicked, this, &AddEmployee::reject);
    connect(ui->addImageButton, &QPushButton::clicked, this, &AddEmployee::on_addImageButton_clicked);

}

AddEmployee::~AddEmployee()
{
    delete ui;
}

// Methods to get data from the dialog inputs
QString AddEmployee::getCin() const { return ui->cinLineEdit->text(); }
QString AddEmployee::getIdEmployee() const { return ui->idEmployeeLineEdit->text(); }
QString AddEmployee::getFullName() const { return ui->fullNameLineEdit->text(); }
QDate AddEmployee::getHireDate() const { return ui->hireDateEdit->date(); }
QString AddEmployee::getRole() const { return ui->roleCombobox->currentText(); }  // Get role from the combobox
double AddEmployee::getSalary() const { return ui->salaryLineEdit->text().toDouble(); }
QString AddEmployee::getEmail() const { return ui->emailLineEdit->text(); }
QDate AddEmployee::getDateOfBirth() const { return ui->birthdaydateedit->date(); }
QString AddEmployee::getGender() const { return ui->genderCombobox->currentText(); }
QString AddEmployee::getPhone() const { return ui->phoneLineEdit->text(); }

// Function to check uniqueness of CIN, ID, Phone, or Email (case-insensitive for ID and Email)
bool AddEmployee::isUnique(const QString &field, const QString &value, bool caseInsensitive) {
    QSqlQuery query;

    if (caseInsensitive) {
        query.prepare(QString("SELECT COUNT(*) FROM EMPLOYEE WHERE LOWER(%1) = LOWER(:value)").arg(field));
    } else {
        query.prepare(QString("SELECT COUNT(*) FROM EMPLOYEE WHERE %1 = :value").arg(field));
    }

    query.bindValue(":value", value);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;  // Check if the count is 0, meaning it's unique
    }
    return false;  // If the query fails, treat it as non-unique
}

// Function to add employee to database with validation
bool AddEmployee::addEmployeeToDatabase() {
    QStringList errorMessages;

    // Validate CIN
    if (getCin().length() != 8 || !getCin().toUInt()) {
        errorMessages.append("CIN must be an 8-digit number.");
    }

    // Validate phone number length
    if (getPhone().length() != 8 || !getPhone().toUInt()) {
        errorMessages.append("Phone must be an 8-digit number.");
    }

    // Check uniqueness of CIN
    if (!isUnique("CINEMP", getCin(), false)) {
        errorMessages.append("CIN must be unique.");
    }

    // Check if ID Employee is unique
    if (getIdEmployee().isEmpty()) {
        errorMessages.append("ID Employee cannot be empty.");
    } else if (!isUnique("IDEMP", getIdEmployee(), true)) {
        errorMessages.append("ID Employee must be unique (case-insensitive).");
    }

    // Check uniqueness of phone
    if (!isUnique("PHONE", getPhone(), false)) {
        errorMessages.append("Phone number must be unique.");
    }

    // Validate hire date
    if (getHireDate() >= QDate::currentDate()) {
        errorMessages.append("Hire date must be earlier than today.");
    }

    // Validate email format
    if (!ui->emailLineEdit->hasAcceptableInput()) {
        errorMessages.append("Email format is invalid.");
    }

    // Check uniqueness of email
    if (!isUnique("EMAIL", getEmail(), true)) {
        errorMessages.append("Email must be unique (case-insensitive).");
    }

    // Validate salary
    if (getSalary() <= 0) {
        errorMessages.append("Salary must be a positive number.");
    }

    if (!errorMessages.isEmpty()) {
        QMessageBox::warning(this, "Validation Errors", errorMessages.join("\n"));
        return false;
    }
    QString imagePath = ui->imagePathLabel->text();
    // Insert into the database
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE (CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE, IMAGE_PATH) "
                  "VALUES (:cinemp, :idemp, :full_name, :hire_date, :role, :salary, :email, :date_of_birth, :gender, :phone, :image_path)");
    query.bindValue(":image_path", imagePath);
    query.bindValue(":cinemp", getCin());
    query.bindValue(":idemp", getIdEmployee());
    query.bindValue(":full_name", getFullName());
    query.bindValue(":hire_date", getHireDate());
    query.bindValue(":role", getRole());  // Get role from combobox
    query.bindValue(":salary", getSalary());
    query.bindValue(":email", getEmail());
    query.bindValue(":date_of_birth", getDateOfBirth());
    query.bindValue(":gender", getGender());
    query.bindValue(":phone", getPhone());

    if (query.exec()) {
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to add employee: " + query.lastError().text());
        return false;
    }
}

void AddEmployee::onOkButtonClicked() {
    if (addEmployeeToDatabase()) {
        accept();
    }
}

void AddEmployee::generateEmployeeId()
{
    QSqlQuery query;

    // Adjusted query to get the maximum IDEMP
    if (query.exec("SELECT MAX(IDEMP) FROM EMPLOYEE")) {
        if (query.next()) {
            QString lastId = query.value(0).toString();  // Get the max IDEMP (e.g., "EMP0005")

            if (!lastId.isEmpty()) {
                QString numericPart = lastId.mid(3);  // Extract numeric part (e.g., "0005")
                int nextIdNumber = numericPart.toInt() + 1;
                ui->idEmployeeLineEdit->setText(QString("EMP%1").arg(nextIdNumber, 4, 10, QChar('0')));
            } else {
                ui->idEmployeeLineEdit->setText("EMP0001");  // First ID if no records exist
            }
        } else {
            ui->idEmployeeLineEdit->setText("EMP0001");  // No rows, start with EMP0001
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
        ui->idEmployeeLineEdit->setText("EMP0001");  // Default in case of query failure
    }

    ui->idEmployeeLineEdit->setReadOnly(true);
}
void AddEmployee::on_addImageButton_clicked() {
    // Open a file dialog to select an image
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Employee Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No image selected.");
        return;
    }

    // Display the selected image in the QLabel
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "Failed to load the image.");
        return;
    }
    ui->imagePathLabel->setPixmap(pixmap.scaled(ui->imagePathLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Optionally store the image path in a class member or database
    //this->imagePath = imagePath; // Assuming you have a class member `QString imagePath`.
}
