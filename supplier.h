#ifndef SUPPLIER_H
#define SUPPLIER_H
#include<string>
#include<QDate>
using namespace std;


class Supplier
{
public:
    Supplier();
    Supplier(int cin,int id, const QString &name,  const QDate &date, const QString &contact,const QString &adr);



    int getCin() const;
    void setCin(int newCin);
    int getId() const;
    void setId(int newId);
    const QString &getName() const;
    void setName(const QString &newName);
    const QDate &getDate() const;
    void setDate(const QDate &newDate);
    const QString &getContact() const;
    void setContact(const QString &newContact);
    const QString &getAdr() const;
    void setAdresse(const QString &newAdr);


private:
    int cin;
    int id;
    QString name;
    QDate date;
    QString contact;
    QString adr;


};

#endif // SUPPLIER_H
