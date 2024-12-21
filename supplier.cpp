#include "supplier.h"
#include "qrcodegen.hpp"

Supplier::Supplier()
{

}
int Supplier::getCin() const
{
    return cin;
}
void Supplier::setCin(int newCin)
{
    cin = newCin;
}
int Supplier::getId() const
{
    return id;
}
void Supplier::setId(int newId)
{
    cin = newId;
}
const QString &Supplier::getName() const
{
    return name;
}
void Supplier::setName(const QString &newName)
{
    name= newName;
}
const QDate &Supplier::getDate() const
{
    return date;
}

void Supplier::setDate(const QDate &newDate)
{
    date = newDate;
}
const QString &Supplier::getContact() const
{
    return contact;
}
void Supplier::setContact(const QString &newContact)
{
    contact= newContact;
}

const QString &Supplier::getAdr() const
{
    return adr;
}
void Supplier::setAdresse(const QString &newAdr)
{
    adr= newAdr;
}
Supplier::Supplier(int cin, int id, const QString &name, const QDate &date, const QString &contact, const QString &adr) :
    cin(cin),
    id(id),
    name(name),
    date(date),
    contact(contact),
    adr(adr)
{
}

