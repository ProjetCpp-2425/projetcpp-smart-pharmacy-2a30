#include "supplier.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

// Default constructor
Employee::Employee() {}

// Parameterized constructor
Employee::Employee(int cinemp, QString idemp, QString fullName, QDate hireDate, QString role, double salary, QString email, int age, QString gender, int phone) {
    this->cinemp = cinemp;
    this->idemp = idemp;
    this->full_name = fullName;
    this->hire_date = hireDate;
    this->role = role;
    this->salary = salary;
    this->email = email;
    this->age = age;
    this->gender = gender;
    this->phone = phone;
}

// Getters
int Employee::getCinEmp() { return cinemp; }
QString Employee::getIdEmp() { return idemp; }
QString Employee::getFullName() { return full_name; }
QDate Employee::getHireDate() { return hire_date; }
QString Employee::getRole() { return role; }
double Employee::getSalary() { return salary; }
QString Employee::getEmail() { return email; }
int Employee::getAge() { return age; }
QString Employee::getGender() { return gender; }
int Employee::getPhone() { return phone; }

// Setters
void Employee::setCinEmp(int cinemp) { this->cinemp = cinemp; }
void Employee::setIdEmp(QString idemp) { this->idemp = idemp; }
void Employee::setFullName(QString fullName) { this->full_name = fullName; }
void Employee::setHireDate(QDate hireDate) { this->hire_date = hireDate; }
void Employee::setRole(QString role) { this->role = role; }
void Employee::setSalary(double salary) { this->salary = salary; }
void Employee::setEmail(QString email) { this->email = email; }
void Employee::setAge(int age) { this->age = age; }
void Employee::setGender(QString gender) { this->gender = gender; }
void Employee::setPhone(int phone) { this->phone = phone; }

// Adding a new employee
bool Employee::addEmployee() {
    QSqlQuery query;
    query.prepare("INSERT INTO employee (cinemp, idemp, full_name, hire_date, role, salary, email, age, gender, phone) "
                  "VALUES (:cinemp, :idemp, :full_name, :hire_date, :role, :salary, :email, :age, :gender, :phone)");
    query.bindValue(":cinemp", cinemp);
    query.bindValue(":idemp", idemp);
    query.bindValue(":full_name", full_name);
    query.bindValue(":hire_date", hire_date);
    query.bindValue(":role", role);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":age", age);
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);

    return query.exec();
}

// Displaying all employees
QSqlQueryModel* Employee::displayEmployees() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee");
    return model;
}

// Deleting an employee by ID
bool Employee::deleteEmployee(QString idemp) {
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE idemp = :idemp");
    query.bindValue(":idemp", idemp);

    return query.exec();
}

// Editing an employee by ID
bool Employee::editEmployee(QString idemp) {
    QSqlQuery query;
    query.prepare("UPDATE employee SET full_name = :full_name, hire_date = :hire_date, role = :role, salary = :salary, email = :email, "
                  "age = :age, gender = :gender, phone = :phone WHERE idemp = :idemp");
    query.bindValue(":idemp", idemp);
    query.bindValue(":full_name", full_name);
    query.bindValue(":hire_date", hire_date);
    query.bindValue(":role", role);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":age", age);
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);

    return query.exec();
}
