#include "addemployee.h"
#include "ui_addemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee)
{
    ui->setupUi(this);
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
QString AddEmployee::getRole() const { return ui->roleLineEdit->text(); }
double AddEmployee::getSalary() const { return ui->salaryLineEdit->text().toDouble(); }
QString AddEmployee::getEmail() const { return ui->emailLineEdit->text(); }
int AddEmployee::getAge() const { return ui->ageLineEdit->text().toInt(); }
QString AddEmployee::getGender() const { return ui->genderLineEdit->text(); }
QString AddEmployee::getPhone() const { return ui->phoneLineEdit->text(); }

// Function to add employee to database
bool AddEmployee::addEmployeeToDatabase() {
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
