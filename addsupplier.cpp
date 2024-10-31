#include "addsupplier.h"
#include "ui_addsupplier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QDate>

AddSupplier::AddSupplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSupplier)
{
    ui->setupUi(this);

    QRegularExpression cinRegEx("\\d{8}");
    QValidator *cinValidator = new QRegularExpressionValidator(cinRegEx, this);
    ui->cinLineEdit->setValidator(cinValidator);



};

AddSupplier::~AddSupplier()
{
    delete ui;
}

// Methods to get data from the dialog inputs
QString AddSupplier::getCin() const { return ui->cinLineEdit->text(); }
QString AddSupplier::getIdSupplier() const { return ui->idSupplierLineEdit->text(); }
QString AddSupplier::getFullName() const { return ui->fullNameLineEdit->text(); }
QDate AddSupplier::getHireDate() const { return ui->hireDateEdit->date(); }
QString AddSupplier::getConctact() const { return ui->contactLineEdit->text(); }
QString AddSupplier::getAdresse() const { return ui->adresseLineEdit->text(); }


// Function to check uniqueness of CIN, ID,contact, or Adresse(case-insensitive for ID and Adresse)
bool AddSupplier::isUnique(const QString &field, const QString &value, bool caseInsensitive) {
    QSqlQuery query;

    // Use case-insensitive comparison for IDEMP and EMAIL
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
    // Validate CIN
    if (getCin().length() != 8 || !getCin().toUInt()) {
        QMessageBox::warning(this, "Validation Error", "CIN must be an 8-digit number.");
        return false;
    }

    // Validate phone number length (must be 8 digits)
    if (getPhone().length() != 8 || !getPhone().toUInt()) {
        QMessageBox::warning(this, "Validation Error", "Phone must be an 8-digit number.");
        return false;
    }

    // Check if CIN is unique
    if (!isUnique("CINEMP", getCin(), false)) {
        QMessageBox::warning(this, "Validation Error", "CIN must be unique.");
        return false;
    }

    // Check if ID Employee is unique (case-insensitive)
    if (getIdEmployee().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "ID Employee cannot be empty.");
        return false;
    }

    if (!isUnique("IDEMP", getIdEmployee(), true)) {
        QMessageBox::warning(this, "Validation Error", "ID Employee must be unique (case-insensitive).");
        return false;
    }

    // Check if Phone is unique
    if (!isUnique("PHONE", getPhone(), false)) {
        QMessageBox::warning(this, "Validation Error", "Phone number must be unique.");
        return false;
    }

    // Validate hire date (must be before today)
    if (getHireDate() >= QDate::currentDate()) {
        QMessageBox::warning(this, "Validation Error", "Hire date must be earlier than today.");
        return false;
    }

    // Validate email format
    if (!ui->emailLineEdit->hasAcceptableInput()) {
        QMessageBox::warning(this, "Validation Error", "Email format is invalid.");
        return false;
    }

    // Check if Email is unique (case-insensitive)
    if (!isUnique("EMAIL", getEmail(), true)) {
        QMessageBox::warning(this, "Validation Error", "Email must be unique (case-insensitive).");
        return false;
    }

    // Validate salary (must be a positive number)
    if (getSalary() <= 0) {
        QMessageBox::warning(this, "Validation Error", "Salary must be a positive number.");
        return false;
    }

    // If all validation checks pass, attempt to insert into the database
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE (CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, AGE, GENDER, PHONE) "
                  "VALUES (:cinemp, :idemp, :full_name, :hire_date, :role, :salary, :email, :age, :gender, :phone)");
    query.bindValue(":cinemp", getCin());
    query.bindValue(":idemp", getIdEmployee());
    query.bindValue(":full_name", getFullName());
    query.bindValue(":hire_date", getHireDate());
    query.bindValue(":role", getRole());
    query.bindValue(":salary", getSalary());
    query.bindValue(":email", getEmail());
    query.bindValue(":age", getAge());
    query.bindValue(":gender", getGender());
    query.bindValue(":phone", getPhone());

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Employee added successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to add employee: " + query.lastError().text());
        return false;
    }
}
