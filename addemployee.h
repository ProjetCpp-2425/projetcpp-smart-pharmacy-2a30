#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
#include "connection.h" // Include the connection class

namespace Ui {
class AddEmployee;
}

class AddEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployee(QWidget *parent = nullptr);
    ~AddEmployee();

    // Methods to get employee data entered
    QString getCin() const;
    QString getIdEmployee() const;
    QString getFullName() const;
    QDate getHireDate() const;
    QString getRole() const;
    double getSalary() const;
    QString getEmail() const;
    int getAge() const;
    QString getGender() const;
    QString getPhone() const;

    // Function to insert employee into the database
    bool addEmployeeToDatabase();

private:
    Ui::AddEmployee *ui;

    // Function to check if a field is unique in the database
    bool isUnique(const QString &field, const QString &value, bool caseInsensitive);  // Add the bool caseInsensitive parameter
};

#endif // ADDEMPLOYEE_H
