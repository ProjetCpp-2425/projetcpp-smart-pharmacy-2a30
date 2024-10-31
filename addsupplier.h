#ifndef ADDSUPPLIER_H
#define ADDSUPPLIER_H

#include <QDialog>
#include "connection.h" // Include the connection class

namespace Ui {
class AddSupplier;
}

class AddSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit AddSupplier(QWidget *parent = nullptr);
    ~AddSupplier();

    // Methods to get supplier data entered
    QString getCin() const;
    QString getIdSupplier() const;
    QString getFullName() const;
    QDate getHireDate() const;
    QString getContact() const;
    QString getAdresse() const;


    // Function to insert supplier into the database
    bool addSupplierToDatabase();

private:
    Ui::AddSupplier *ui;

    // Function to check if a field is unique in the database
    bool isUnique(const QString &field, const QString &value, bool caseInsensitive);  // Add the bool caseInsensitive parameter
};

#endif // ADDSUPPLIER_H
