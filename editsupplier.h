#ifndef EDITSUPPLIER_H
#define EDITSUPPLIER_H

#include <QDialog>
#include <QDate>

namespace Ui {
class EditSupplier;
}

class EditSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit EditSupplier(QWidget *parent = nullptr);
    ~EditSupplier();

    // Method to set supplier data in the dialog's fields
    void setSupplierData(const QString &cin, const QString &id, const QString &fullName, const QDate &hireDate,
                         const QString &contact, const QString &adresse);

    // Method to update the supplier in the database
    bool updateSupplierInDatabase();

private:
    Ui::EditSupplier *ui;
    QString currentCin;  // Store the current CIN to identify the supplier during the update
};

#endif // EDITSUPPLIER_H
