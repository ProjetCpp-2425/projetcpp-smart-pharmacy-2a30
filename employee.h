#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Employee {
public:
    // Default constructor
    Employee();
    static int calculateAge(const QDate &dateOfBirth);
    // Parameterized constructor
    Employee(int cinemp, QString idemp, QString fullName, QDate hireDate, QString role, double salary, QString email, QDate dateOfBirth, QString gender, int phone);

    // Getters
    int getCinEmp();
    QString getIdEmp();
    QString getFullName();
    QDate getHireDate();
    QString getRole();
    double getSalary();
    QString getEmail();
    QDate getDateOfBirth();  // Getter for date of birth
    QString getGender();
    int getPhone();
    QSqlQueryModel* sortEmployees(QString criterion);
    // Setters
    void setCinEmp(int cinemp);
    void setIdEmp(QString idemp);
    void setFullName(QString fullName);
    void setHireDate(QDate hireDate);
    void setRole(QString role);
    void setSalary(double salary);
    void setEmail(QString email);
    void setDateOfBirth(QDate dateOfBirth);  // Setter for date of birth
    void setGender(QString gender);
    void setPhone(int phone);

    // Calculates age based on date of birth
    int calculateAge() const;

    // Database operations
    bool addEmployee();
    QSqlQueryModel* displayEmployees();
    bool deleteEmployee(QString idemp);
    bool editEmployee(QString idemp);

private:
    int cinemp;              // CINEMP: Employee CIN
    QString idemp;           // IDEMP: Employee ID
    QString full_name;       // FULL_NAME: Employee's full name
    QDate hire_date;         // HIRE_DATE: Employee's hire date
    QString role;            // ROLE: Employee's role
    double salary;           // SALARY: Employee's salary
    QString email;           // EMAIL: Employee's email
    QDate date_of_birth;     // DATE_OF_BIRTH: Employee's date of birth
    QString gender;          // GENDER: Employee's gender
    int phone;               // PHONE: Employee's phone number
};

#endif // EMPLOYEE_H
