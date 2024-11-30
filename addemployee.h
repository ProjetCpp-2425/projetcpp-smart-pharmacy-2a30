#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
#include <QDate>
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
    QString getRole() const;  // Now retrieves the selected role from roleCombobox
    double getSalary() const;
    QString getEmail() const;
    QDate getDateOfBirth() const;  // Changed from getAge to getDateOfBirth
    QString getGender() const;
    QString getPhone() const;

    // Function to insert employee into the database
    bool addEmployeeToDatabase();
    void clearFields();
    void generateEmployeeId();



public slots:
    void onOkButtonClicked();

private:
    Ui::AddEmployee *ui;

    // Function to check if a field is unique in the database
    bool isUnique(const QString &field, const QString &value, bool caseInsensitive);
private slots :
    void on_addImageButton_clicked();
};

#endif // ADDEMPLOYEE_H
