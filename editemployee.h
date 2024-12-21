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
                         const QString &role, double salary, const QString &email, const QDate &dateOfBirth,  // Updated: replaced int age with QDate dateOfBirth
                         const QString &gender, const QString &phone);

    // Methods to handle employee updates
    bool validateInputs();
    bool updateEmployeeInDatabase();

public slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::EditEmployee *ui;
    QString currentCin;  // Store the current CIN to identify the employee during the update
};

#endif // EDITEMPLOYEE_H
