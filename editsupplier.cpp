#include "editsupplier.h"
#include "ui_editemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

EditEmployee::EditEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployee)
{
    ui->setupUi(this);
}

EditEmployee::~EditEmployee()
{
    delete ui;
}

// Set the current employee data into the dialog's fields
void EditEmployee::setEmployeeData(const QString &cin, const QString &id, const QString &fullName, const QDate &hireDate,
                                   const QString &role, double salary, const QString &email, int age,
                                   const QString &gender, const QString &phone)
{
    currentCin = cin;  // Store the CIN to identify the employee later during the update
    ui->cinLineEdit->setText(cin);
    ui->idEmployeeLineEdit->setText(id);
    ui->fullNameLineEdit->setText(fullName);
    ui->hireDateEdit->setDate(hireDate);
    ui->roleLineEdit->setText(role);
    ui->salaryLineEdit->setText(QString::number(salary));
    ui->emailLineEdit->setText(email);
    ui->ageLineEdit->setValue(age);
    ui->genderCombobox->setCurrentText(gender);  // Set the gender combobox value
    ui->phoneLineEdit->setText(phone);
}

// Update the employee's information in the database
bool EditEmployee::updateEmployeeInDatabase()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET "
                  "IDEMP = :id, FULL_NAME = :full_name, HIRE_DATE = :hire_date, ROLE = :role, "
                  "SALARY = :salary, EMAIL = :email, AGE = :age, GENDER = :gender, PHONE = :phone "
                  "WHERE CINEMP = :cin");

    query.bindValue(":id", ui->idEmployeeLineEdit->text());
    query.bindValue(":full_name", ui->fullNameLineEdit->text());
    query.bindValue(":hire_date", ui->hireDateEdit->date());
    query.bindValue(":role", ui->roleLineEdit->text());
    query.bindValue(":salary", ui->salaryLineEdit->text().toDouble());
    query.bindValue(":email", ui->emailLineEdit->text());
    query.bindValue(":age", ui->ageLineEdit->text().toInt());
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
