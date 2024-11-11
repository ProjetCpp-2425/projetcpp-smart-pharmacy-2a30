#include "product.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

// Default Constructor
Product::Product() {}

// Parameterized Constructor
Product::Product(int id, QString date, float montant, QString stat, int quantite, QString expirationDate, float price)
    : id_pro(id), date_comm(date), montant_total(montant), status(stat), quantite(quantite), date_expiration(expirationDate), prix(price) {}

// Method to add a product to the database
bool Product::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO product (id_pro, date_comm, montant_total, status, quantite, date_expiration, prix) "
                  "VALUES (:id, :date, :montant, :stat, :quantite, :date_expiration, :prix)");
    query.bindValue(":id", id_pro);
    query.bindValue(":date", date_comm);
    query.bindValue(":montant", montant_total);
    query.bindValue(":stat", status);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_expiration", date_expiration);
    query.bindValue(":prix", prix);

    if (!query.exec()) {
        qDebug() << "Error adding product:" << query.lastError().text();
        return false;
    }
    return true; // Return true if insertion was successful
}

// Method to display products from the database
// Method to display products from the database
QSqlQueryModel* Product::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM product ORDER BY quantite ASC");

    // Set headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Product ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date of Command"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Amount"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Expiration Date"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Price"));

    return model;
}


// Method to delete a product from the database by ID
bool Product::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM product WHERE id_pro = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting product:" << query.lastError().text();
        return false;
    }
    return true;
}

// Method to modify/display products based on a search term
QSqlQueryModel* Product::modifier(const QString &searchTerm) {
    QSqlQuery query;
    query.prepare("SELECT id_pro, date_comm, montant_total, status FROM product WHERE id_pro LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error modifying product:" << query.lastError().text();
        return nullptr; // Return null if query fails
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    // Set headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Product ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date of Command"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Total Amount"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status"));

    return model;
}
