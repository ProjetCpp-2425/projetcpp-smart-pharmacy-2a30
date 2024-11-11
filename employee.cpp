#include "employee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QVariant> // For QVariant binding

// Default constructor
Employee::Employee() {}

// Parameterized constructor
Employee::Employee(int cinemp, QString idemp, QString fullName, QDate hireDate, QString role, double salary, QString email, QDate dateOfBirth, QString gender, int phone) {
    this->cinemp = cinemp;
    this->idemp = idemp;
    this->full_name = fullName;
    this->hire_date = hireDate;
    this->role = role;
    this->salary = salary;
    this->email = email;
    this->date_of_birth = dateOfBirth;  // Replacing age with date_of_birth
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
QDate Employee::getDateOfBirth() { return date_of_birth; }  // Getter for date of birth
QString Employee::getGender() { return gender; }
int Employee::getPhone() { return phone; }

// Setter
void Employee::setCinEmp(int cinemp) { this->cinemp = cinemp; }
void Employee::setIdEmp(QString idemp) { this->idemp = idemp; }
void Employee::setFullName(QString fullName) { this->full_name = fullName; }
void Employee::setHireDate(QDate hireDate) { this->hire_date = hireDate; }
void Employee::setRole(QString role) { this->role = role; }
void Employee::setSalary(double salary) { this->salary = salary; }
void Employee::setEmail(QString email) { this->email = email; }
void Employee::setDateOfBirth(QDate dateOfBirth) { this->date_of_birth = dateOfBirth; }  // Setter for date of birth
void Employee::setGender(QString gender) { this->gender = gender; }
void Employee::setPhone(int phone) { this->phone = phone; }

// Calculate age based on date of birth
int Employee::calculateAge() const {
    return QDate::currentDate().year() - date_of_birth.year() - (QDate::currentDate().dayOfYear() < date_of_birth.dayOfYear() ? 1 : 0);
}

// Adding a new employee
bool Employee::addEmployee() {
    QSqlQuery query;
    query.prepare("INSERT INTO employee (cinemp, idemp, full_name, hire_date, role, salary, email, date_of_birth, gender, phone) "
                  "VALUES (:cinemp, :idemp, :full_name, :hire_date, :role, :salary, :email, :date_of_birth, :gender, :phone)");
    query.bindValue(":cinemp", cinemp);
    query.bindValue(":idemp", idemp);
    query.bindValue(":full_name", full_name);
    query.bindValue(":hire_date", hire_date);
    query.bindValue(":role", role);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":date_of_birth", date_of_birth);  // Use date of birth
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);

    return query.exec();
}

// Displaying all employees (and calculating age on the fly)
QSqlQueryModel* Employee::displayEmployees() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT cinemp, idemp, full_name, hire_date, role, salary, email, "
                    "EXTRACT(YEAR FROM SYSDATE) - EXTRACT(YEAR FROM date_of_birth) - "
                    "(TO_CHAR(SYSDATE, 'MMDD') < TO_CHAR(date_of_birth, 'MMDD')) AS age, "
                    "gender, phone FROM employee");
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
                  "date_of_birth = :date_of_birth, gender = :gender, phone = :phone WHERE idemp = :idemp");
    query.bindValue(":idemp", idemp);
    query.bindValue(":full_name", full_name);
    query.bindValue(":hire_date", hire_date);
    query.bindValue(":role", role);
    query.bindValue(":salary", salary);
    query.bindValue(":email", email);
    query.bindValue(":date_of_birth", date_of_birth);  // Update date of birth
    query.bindValue(":gender", gender);
    query.bindValue(":phone", phone);

    return query.exec();
}

// Sorting employees
QSqlQueryModel* Employee::sortEmployees(QString criterion) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM employee ORDER BY " + criterion;
    model->setQuery(queryStr);

    return model;
}
int Employee::calculateAge(const QDate &dateOfBirth)
{
    if (!dateOfBirth.isValid()) {
        qDebug() << "Invalid date of birth provided!";
        return 0;  // Return 0 for invalid dates
    }

    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - dateOfBirth.year();

    // Adjust age if the birthday hasn't occurred yet this year
    if (currentDate < dateOfBirth.addYears(age)) {
        age--;
    }

    qDebug() << "Date of Birth Year:" << dateOfBirth.year() << ", Current Year:" << currentDate.year() << ", Calculated Age:" << age;

    return age;
}
