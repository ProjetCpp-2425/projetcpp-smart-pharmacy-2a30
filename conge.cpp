#include "conge.h"
#include "conge.h"
#include "qtextcursor.h"
#include "qtextdocument.h"
#include <QSqlQuery>
#include <QVariant>
#include<QSqlError>
#include<QMessageBox>
#include <QSqlQueryModel>
#include <QHeaderView>

conge::conge(int IDE, int IDC, QString DATEDEB, QString TYPE, int PERIODE, QString STATUT)
{
    this->IDE=IDE;
    this->IDC=IDC;
    this->DATEDEB=DATEDEB;
    this->TYPE=TYPE;
    this->PERIODE=PERIODE;
    this->STATUT=STATUT;


}

//new
bool conge::ajouterConge(int IDC, int IDE, QString DATEDEB, QString TYPE, int PERIODE, QString STATUT) {
    // Exemple de code pour ajouter le congé
    // Vous pouvez ici ajouter le congé dans une base de données ou une structure de données.
    QSqlQuery query;
    query.prepare("INSERT INTO Conge (IDC, IDE, DATEDEB, TYPE, PERIODE, STATUT) VALUES (:IDC, :IDE, :DATEDEB, :TYPE, :PERIODE, :STATUT)");
    query.bindValue(":IDC", IDC);
    query.bindValue(":IDE", IDE);
    query.bindValue(":DATEDEB", DATEDEB);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":PERIODE", PERIODE);
    query.bindValue(":STATUT", STATUT);

    if (query.exec()) {
        return true; // Le congé a été ajouté avec succès
    } else {
        return false; // Échec de l'ajout du congé
    }
}
bool conge::mettreAJourStatut(int IDE, const QString &nouveauStatut) {
    // Vérifier le statut actuel de l'employé
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT STATUTE FROM employe WHERE IDE = :IDE");
    checkQuery.bindValue(":IDE", IDE);

    if (!checkQuery.exec()) {
        // Gérer l'erreur de la requête
        qDebug() << "Erreur lors de la vérification du statut de l'employé :" << checkQuery.lastError().text();
        return false;
    }

    if (checkQuery.next()) {
        QString statutActuel = checkQuery.value(0).toString();
        if (statutActuel == "inactif") {
            // Si l'employé est déjà inactif, retourner un message d'erreur
            QMessageBox::warning(nullptr, "Erreur", "Employé déjà inactif, impossible d'attribuer un congé.");
            return false; // Indique que la mise à jour n'a pas été effectuée
        }
    } else {
        // Si aucun employé n'est trouvé avec cet ID
        QMessageBox::critical(nullptr, "Erreur", "Aucun employé trouvé avec cet ID.");
        return false;
    }

    // Si le statut n'est pas inactif, procéder à la mise à jour
    QSqlQuery query;
    query.prepare("UPDATE employe SET STATUTE = :nouveauStatut WHERE IDE = :IDE");
    query.bindValue(":nouveauStatut", nouveauStatut);
    query.bindValue(":IDE", IDE);

    return query.exec();
}

/*QSqlQueryModel* conge::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Vérification de la connexion
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Erreur : Connexion à la base de données fermée.";
        return model;
    }

    // Préparer la requête
    QSqlQuery query("SELECT * FROM CONGE");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
        return model;
    }

    // Associer les données au modèle
    model->setQuery(query);

    // Vérification du contenu
    qDebug() << "Nombre de lignes récupérées : " << model->rowCount();

    // Configuration des en-têtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEDEB"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PERIODE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}

void conge::afficherDansTableView(QTableView* tableView_2) {
    QSqlQueryModel* model = afficher();

    if (!model || model->rowCount() == 0) {
        qDebug() << "Erreur : Aucune donnée à afficher.";
        return;
    }

    tableView_2->setModel(model);
    tableView_2->resizeColumnsToContents();
    tableView_2->horizontalHeader()->setStretchLastSection(true);

    qDebug() << "Affichage terminé dans QTableView.";
}*/
QSqlQueryModel * conge::afficher(){
        QSqlQueryModel * model =new QSqlQueryModel();
        model->setQuery("select * from CONGE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDC"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATEDEB"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PERIODE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT"));

        return model;
    }
