#ifndef VENTES_H
#define VENTES_H
#include "qdatetime.h"
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlError>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QPainter>

class Ventes
{
private:
    int ID_VENTE,QUANTITE;
    QString CODEMEDIC,DESIGNIATION;
    float PRIX,TOTALHT;
    QDate SDATE;


public:
    Ventes(){}
    Ventes(int ID_VENTE, float PRIX, int QUANTITE, float TOTALHT, QString CODEMEDIC, QString DESIGNIATION, QDate SDATE);
    int getID(){return ID_VENTE;}
    float getPRIX(){return PRIX;}
    int getQUANTITE(){return QUANTITE;}
    float getTOTALHT(){return TOTALHT;}
    QString getCode(){return CODEMEDIC;}
    QString getDESIGNIATION(){return DESIGNIATION;}
    QDate getSDATE(){return SDATE;}


    void setID(int id){this ->ID_VENTE=id;}
    void setPRIX(float PRIX){this ->PRIX=PRIX;}
    void setQUANTITE(int QUANTITE){this ->QUANTITE=QUANTITE;}
    void settotal(float TOTALHT){this->TOTALHT=TOTALHT;}
    void setcode(QString CODEMEDIC){this->CODEMEDIC=CODEMEDIC;}
    void setDESIGNIATION(QString DESIGNIATION){this->DESIGNIATION=DESIGNIATION;}
    void setDATE(QDate SDATE){this->SDATE=SDATE;}

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int ID_VENTE);
    bool loadVentesdata(int ID_VENTE); // Charge les données de l'employé par ID
    bool modifier(int ID_VENTE);
    bool checkIfID_VENTExists(int ID_VENTE);
    Ventes getVentesById(int ID_VENTE);
    //new
    QSqlQueryModel* trier(const QString& critere);
    QSqlQueryModel *chercher(const QString &critere);
    QSqlQueryModel* getStatistics();
    QSqlQueryModel* getHistorique();
    // Method declaration

   };


//new




#endif // VENTES_H
