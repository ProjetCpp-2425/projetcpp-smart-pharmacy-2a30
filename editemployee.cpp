#include "editemployee.h"
#include "ui_editemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>  // For debugging

EditEmployee::EditEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployee)
{
    ui->setupUi(this);
    this->setWindowTitle("EDIT Employee ;)");
    connect(ui->okbutton, &QPushButton::clicked, this, &EditEmployee::onOkButtonClicked);
    connect(ui->cancelbutton, &QPushButton::clicked, this, &EditEmployee::onCancelButtonClicked);
}

EditEmployee::~EditEmployee()
{
    delete ui;
}

// Set the current employee data into the dialog's fields
void EditEmployee::setEmployeeData(const QString &cin, const QString &id, const QString &fullName, const QDate &hireDate,
                                   const QString &role, double salary, const QString &email, const QDate &dateOfBirth,
                                   const QString &gender, const QString &phone)
{
    currentCin = cin;  // Store the CIN to identify the employee later during the update
    ui->cinLineEdit->setText(cin);
    ui->idEmployeeLineEdit->setText(id);
    ui->idEmployeeLineEdit->setReadOnly(true);  // Make the ID field read-only
    ui->fullNameLineEdit->setText(fullName);
    ui->hireDateEdit->setDate(hireDate);
    ui->roleCombobox->setCurrentText(role);  // Set the value in the role combobox
    ui->salaryLineEdit->setText(QString::number(salary));
    ui->emailLineEdit->setText(email);
    ui->birthdaydateedit->setDate(dateOfBirth);  // Set the date of birth
    ui->genderCombobox->setCurrentText(gender);  // Set the gender combobox value
    ui->phoneLineEdit->setText(phone);
}

// Update the employee's information in the database
bool EditEmployee::updateEmployeeInDatabase()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET "
                  "FULL_NAME = :full_name, HIRE_DATE = :hire_date, ROLE = :role, "
                  "SALARY = :salary, EMAIL = :email, DATE_OF_BIRTH = :date_of_birth, GENDER = :gender, PHONE = :phone "
                  "WHERE CINEMP = :cin");

    query.bindValue(":full_name", ui->fullNameLineEdit->text());
    query.bindValue(":hire_date", ui->hireDateEdit->date());
    query.bindValue(":role", ui->roleCombobox->currentText());  // Get role from combobox
    query.bindValue(":salary", ui->salaryLineEdit->text().toDouble());
    query.bindValue(":email", ui->emailLineEdit->text());
    query.bindValue(":date_of_birth", ui->birthdaydateedit->date());  // Bind date of birth
    query.bindValue(":gender", ui->genderCombobox->currentText());
    query.bindValue(":phone", ui->phoneLineEdit->text());
    query.bindValue(":cin", currentCin);  // Use the stored CIN to update the correct employee

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Employee updated successfully.");
        return true;
    } else {
        QMessageBox::warning(this, "Error", "Failed to update employee: " + query.lastError().text());
        return false;
    }
}

void EditEmployee::onOkButtonClicked()
{
    if (!validateInputs()) {
        return;  // Do not proceed if inputs are invalid
    }

    if (updateEmployeeInDatabase()) {
        accept();  // Close the dialog with an accepted state if update succeeds
    }
}

void EditEmployee::onCancelButtonClicked()
{
    reject();  // Close the dialog with a rejected state
}

bool EditEmployee::validateInputs()
{
    bool valid = true;
    QString errorMessage;

    if (ui->fullNameLineEdit->text().isEmpty()) {
        valid = false;
        errorMessage += "Full name cannot be empty.\n";
    }
    if (ui->roleCombobox->currentText().isEmpty()) {  // Validate role selection
        valid = false;
        errorMessage += "Role must be selected.\n";
    }
    if (ui->salaryLineEdit->text().toDouble() <= 0) {
        valid = false;
        errorMessage += "Salary must be a positive number.\n";
    }
    if (ui->emailLineEdit->text().isEmpty() || !ui->emailLineEdit->text().contains('@')) {
        valid = false;
        errorMessage += "Invalid email address.\n";
    }
    if (ui->birthdaydateedit->date() >= QDate::currentDate()) {
        valid = false;
        errorMessage += "Date of birth must be earlier than today.\n";
    }
    if (ui->phoneLineEdit->text().isEmpty() || ui->phoneLineEdit->text().length() != 8) {
        valid = false;
        errorMessage += "Phone number must be 8 digits long.\n";
    }

    if (!valid) {
        QMessageBox::warning(this, "Input Error", errorMessage);
    }

    return valid;
}
