#include "ventes.h"
#include "qdatetime.h"
#include "qtextcursor.h"
#include "qtextdocument.h"
#include <QSqlQuery>
#include <QVariant>
#include<QSqlError>


Ventes::Ventes(int ID_VENTE, float PRIX, int QUANTITE, float TOTALHT, QString CODEMEDIC, QString DESIGNIATION, QDate SDATE)
{
    this->ID_VENTE=ID_VENTE;
    this->PRIX=PRIX;
    this->QUANTITE=QUANTITE;
    this->TOTALHT=TOTALHT;
    this->CODEMEDIC=CODEMEDIC;
    this->DESIGNIATION=DESIGNIATION;
    this->SDATE=SDATE;
}

//new


bool Ventes ::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO SALES (ID_VENTE,PRIX,QUANTITE ,TOTALHT,CODEMEDIC,DESIGNIATION,SDATE)"
                  "VALUES( :ID_VENTE, :PRIX, :QUANTITE, :TOTALHT, :CODEMEDIC, :DESIGNIATION, :SDATE)");
   query.bindValue(":ID_VENTE",ID_VENTE);
   query.bindValue(":PRIX",PRIX);
   query.bindValue(":QUANTITE",QUANTITE);
   query.bindValue(":TOTALHT",TOTALHT);
   query.bindValue(":CODEMEDIC",CODEMEDIC);
   query.bindValue(":DESIGNIATION",DESIGNIATION);
   query.bindValue(":SDATE",SDATE);
   return query.exec();
}
QSqlQueryModel * Ventes ::afficher(){
        QSqlQueryModel * model =new QSqlQueryModel();
        model->setQuery("select * from SALES");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_VENTE"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRIX"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("TOTALHT"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("CODEMEDIC"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("DESIGNIATION"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("SDATE"));

        return model;
    }
bool Ventes::checkIfID_VENTExists(int ID_VENTE)
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM SALES WHERE ID_VENTE = :ID_VENTE");
        query.bindValue(":IDE", ID_VENTE);


        if (query.exec()) {
                if (query.next() && query.value(0).toInt() > 0) {
                    return true; // L'ID existe
                }
            }

            // Si la requête échoue ou si l'ID n'existe pas
            return false;
}
Ventes Ventes ::getVentesById(int ID_VENTE)
{
    QSqlQuery query;
    Ventes Ventes;

    query.prepare("SELECT * FROM SALES WHERE ID_VENTE= :ID_VENTE");
    query.bindValue(":ID_VENTE", ID_VENTE);


    if(query.exec() && query.next())
    {
        Ventes.setID(query.value(0).toInt());
        Ventes.setPRIX(query.value(1).toFloat());
        Ventes.setQUANTITE(query.value(2).toInt());
        Ventes.settotal(query.value(3).toFloat());
        Ventes.setcode(query.value(4).toString());
        Ventes.setDESIGNIATION(query.value(5).toString());
        Ventes.setDATE(query.value(2).toDate());

    }
    return Ventes;
}
bool Ventes::supprimer(int ID_VENTE)
{
    QSqlQuery query;
    QString res=QString::number(ID_VENTE);
    query.prepare("delete from SALES where ID_VENTE=:ID_VENTE");
    query.bindValue(":ID_VENTE",res);
    return query.exec();
}

bool Ventes::loadVentesdata(int ID_VENTE) {
    QSqlQuery query;
    query.prepare("SELECT * FROM SALES WHERE ID_VENTE = :ID_VENTE");
    query.bindValue(":ID_VENTE", ID_VENTE);

    if (query.exec() && query.next()) {
        // Charger les valeurs des colonnes
        this->ID_VENTE = query.value("ID_VENTE").toInt();
        PRIX = query.value("PRIX").toFloat();
        QUANTITE = query.value("QUANTITE").toInt();
        TOTALHT = query.value("TOTALHT").toFloat();
        CODEMEDIC = query.value("CODEMEDIC").toString();
        DESIGNIATION = query.value("DESIGNIATION").toString();
        SDATE = query.value("SDATE").toDate();

        return true;
    } else {

        qWarning() << "Erreur lors du chargement de VENTES :" << query.lastError().text();
        return false;
    }
}
bool Ventes::modifier(int ID_VENTE)
{
    QSqlQuery query;

    // Prepare the query
    query.prepare("UPDATE SALES SET "
                  "PRIX = :PRIX, "
                  "QUANTITE = :QUANTITE, "
                  "TOTALHT = :TOTALHT, "
                  "CODEMEDIC = :CODEMEDIC, "
                  "DESIGNIATION = :DESIGNIATION, "
                  "SDATE = TO_DATE(:SDATE, 'YYYY-MM-DD') "
                  "WHERE ID_VENTE = :ID_VENTE");

    // Bind the values
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":TOTALHT", TOTALHT);
    query.bindValue(":CODEMEDIC", CODEMEDIC);
    query.bindValue(":DESIGNIATION", DESIGNIATION);
    query.bindValue(":SDATE", SDATE.toString("yyyy-MM-dd")); // Format the date
    query.bindValue(":ID_VENTE", ID_VENTE);

    // Execute the query and return the result
    if (!query.exec()) {
        qWarning() << "Erreur lors de la modification de VENTES :" << query.lastError().text();
        return false;
    }

    return true;
}


QSqlQueryModel *Ventes::chercher(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Ensure that the input is sanitized and valid
    if (critere.isEmpty()) {
        qWarning() << "Empty search criteria provided.";
        return nullptr;
    }

    // Query to search for IDs starting with the given criteria
    query.prepare("SELECT * FROM SALES WHERE ID_VENTE LIKE :critere");
    query.bindValue(":critere", critere + "%"); // Match prefix

    if (query.exec()) {
        model->setQuery(query);

        // Set headers for the table view
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_VENTE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TOTALHT"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("CODEMEDIC"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DESIGNIATION"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("SDATE"));

        return model;
    } else {
        // Log an error if the query execution fails
        qWarning() << "Error executing search query:" << query.lastError().text();
        return nullptr;
    }
}



QSqlQueryModel* Ventes::trier(const QString& critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    if (critere == "Date") {
        queryStr = "SELECT * FROM SALES ORDER BY SDATE";
    } else if (critere == "prix") {
        queryStr = "SELECT * FROM SALES ORDER BY PRIX";
    } else if (critere == "quantite") {
        queryStr = "SELECT * FROM SALES ORDER BY QUANTITE";
    }

    // Exécuter la requête
    QSqlQuery query;
    if (query.exec(queryStr)) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur de tri : " << query.lastError();
    }

    return model;
}

QSqlQueryModel* Ventes::getHistorique() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the query without a date range
    query.prepare("SELECT ID_VENTE, PRIX, CODEMEDIC, DESIGNIATION, QUANTITE, TOTALHT, SDATE FROM SALES");

    // Execute the query
    if (!query.exec()) {
        qWarning() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return nullptr;
    }

    // Set the query results in the model
    model->setQuery(query);
    return model;
}

