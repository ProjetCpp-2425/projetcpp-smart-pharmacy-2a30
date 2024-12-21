#ifndef CONGE_H
#define CONGE_H
#include "qtableview.h"
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

class conge
{
private:
    int  IDC,IDE, PERIODE;
    QString DATEDEB,TYPE,STATUT;


public:
    conge(){}
    conge(int IDE, int IDC, QString DATEDEB, QString TYPE, int PERIODE, QString STATUT);
    int getIDE(){return IDE;}
    int getIDC(){return IDC;}
    QString getDATEDEB(){return DATEDEB ;}
    QString getTYPE(){return TYPE;}
    int getPERIODE(){return PERIODE;}
    QString getSTATUT(){return STATUT;}


    void setIDE(int ide){this ->IDE=ide;}
    void setIDC(int idc){this ->IDC=idc;}
    void setDATEDEB(QString DATEDEB){this ->DATEDEB=DATEDEB;}
    void setTYPE(QString TYPE){this ->TYPE=TYPE;}
    void setPERIODE(int PERIODE){this ->PERIODE=PERIODE;}
    void setSTATUT(QString STATUT ){this->STATUT=STATUT;}


    bool ajouterConge(int,int,QString,QString,int,QString);
    bool mettreAJourStatut(int IDE, const QString &nouveauStatut); // Met à jour le statut
    QSqlQueryModel* afficher();
    void afficherDansTableView(QTableView* tableView_2);

   };





#endif // CONGE_H
