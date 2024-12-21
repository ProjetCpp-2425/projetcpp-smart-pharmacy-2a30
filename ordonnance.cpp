#include "ordonnance.h"
#include "qsqlerror.h"
#include <QDebug>

// Debugging function to check database connection
bool checkDatabaseConnection() {
    QSqlDatabase db = QSqlDatabase::database(); // Get the default database connection
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return false;
        }
    }
    return true;
}

// Constructor definition with new attributes
Ordonnance::Ordonnance(int IdPre, QString Reference, QString DrName, QString Instructions) {
    this->IdPre = IdPre;
    this->Reference = Reference;
    this->DrName = DrName;
    this->Instructions = Instructions;
}

bool Ordonnance::ajouter() {
    if (!checkDatabaseConnection()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO ORDONNANCE (ID_PRE, REFERENCE, DR_NAME, INSSTRUCTIONS) "
                  "VALUES (:IdPre, :Reference, :DrName, :Instructions)");

    query.bindValue(":IdPre", IdPre);
    query.bindValue(":Reference", Reference);
    query.bindValue(":DrName", DrName);
    query.bindValue(":Instructions", Instructions);

    if (!query.exec()) {
        qDebug() << "Error adding ordonnance:" << query.lastError().text();
        return false;
    }
    return true;
}

// Displaying all reclamations
QSqlQueryModel* Ordonnance::display() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ORDONNANCE");

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdPre"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DrName"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Instructions"));

    return model;
}

bool Ordonnance::supprimer(int IdPre) {
    if (!checkDatabaseConnection()) return false;

    QSqlQuery query;
    query.prepare("DELETE FROM ORDONNANCE WHERE ID_PRE = :IdPre");
    query.bindValue(":IdPre", IdPre);

    if (!query.exec()) {
        qDebug() << "Error deleting ordonnance:" << query.lastError().text();
        return false;
    }
    return true;
}
bool Ordonnance::modifier(){
    QSqlQuery query;
    QString ID_PREStr = QString::number(IdPre);



    query.prepare("UPDATE ORDONNANCE SET REFERENCE = :Reference, DR_NAME = :DrName, INSSTRUCTIONS = :Instructions  WHERE ID_PRE = :IdPre");
    query.bindValue(":IdPre", IdPre);
    query.bindValue(":Reference", Reference);
    query.bindValue(":DrName", DrName);
    query.bindValue(":Instructions", Instructions);

    return query.exec();
}
QMap<QString, int> Ordonnance::Statistics()
{
    QMap<QString, int> statistics;

    QSqlQuery query;
    query.prepare("SELECT DR_NAME, COUNT(*) AS count FROM ORDONNANCE GROUP BY DR_NAME");
    if (query.exec()) {
        while (query.next()) {
            QString type = query.value("DR_NAME").toString();
            int count = query.value("count").toInt();
            statistics[type] = count;
        }
    }

    return statistics;
}


