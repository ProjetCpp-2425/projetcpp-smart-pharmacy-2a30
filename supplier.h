#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Supplier {
public:
    // Default constructor
    Supplier();

    // Parameterized constructor
    Supplier(int cinsup, QString idsup, QString fullName, QDate hireDate, QString contact, QString adresse);

    // Getters
    int getCinSup();
    QString getIdSup();
    QString getFullName();
    QDate getHireDate();
    QString getContact();
    QString getAdresse();

    // Setters
    void setCinSup(int cinsup);
    void setIdSup(QString idsup);
    void setFullName(QString fullName);
    void setHireDate(QDate hireDate);
    void setContact(QString contact);
    void setAdresse(QString adresse);

    // Database operations
    bool addSupplier();
    QSqlQueryModel* displaySuppliers();
    bool deleteSupplier(QString idsup);
    bool editSupplier(QString idsup);

private:
    int cinsup;              // CINSUP: supplier CIN
    QString idsup;           // IDSUP: supplier ID
    QString full_name;       // FULL_NAME: supplier's full name
    QDate hire_date;         // HIRE_DATE: supplier's hire date
    QString contact;            //CONTACT: supplier's contact
    QString adresse;           // ADRESSE: supplier's adresse

};

#endif // SUPPLIER_H
