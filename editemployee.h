#ifndef EDITEMPLOYEE_H
#define EDITEMPLOYEE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class EditEmployee;
}

class EditEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployee(QWidget *parent = nullptr);
    ~EditEmployee();

    // Method to set employee data in the dialog's fields
    void setEmployeeData(const QString &cin, const QString &id, const QString &fullName, const QDate &hireDate,
                         const QString &role, double salary, const QString &email, int age,
                         const QString &gender, const QString &phone);

    // Method to update the employee in the database
    bool updateEmployeeInDatabase();

private:
    Ui::EditEmployee *ui;
    QString currentCin;  // Store the current CIN to identify the employee during the update
};

#endif // EDITEMPLOYEE_H
