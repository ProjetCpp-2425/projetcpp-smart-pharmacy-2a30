#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");//inserer le nom de la source de données
db.setUserName("projetcpp2a30");//inserer nom de l'utilisateur
db.setPassword("2a30user");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
