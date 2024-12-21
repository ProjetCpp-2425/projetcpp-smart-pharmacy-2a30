#include "product.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

// Default Constructor
Product::Product() {}

// Parameterized Constructor
Product::Product(int id, QDate date, float montant, QString stat, int quantite, QDate expirationDate, float price)
    : id_pro(id), date_comm(date), montant_total(montant), status(stat), quantite(quantite), date_expiration(expirationDate), prix(price) {}


// Method to add a product to the database
bool Product::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO product (id_pro, DATE_COMM, MONTANT_TOTAL, STATUS, QUANTITE, DATE_EXPIRATION, PRIX) "
                  "VALUES (:id, TO_DATE(:date, 'YYYY-MM-DD'), :montant, :status, :quantite, TO_DATE(:date_expiration, 'YYYY-MM-DD'), :prix)");

    // Bind the values
    query.bindValue(":id", id_pro);
    query.bindValue(":date", date_comm.toString("yyyy-MM-dd"));  // Convert QDate to string for SQL
    query.bindValue(":montant", montant_total);
    query.bindValue(":status", status);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_expiration", date_expiration.toString("yyyy-MM-dd"));  // Convert QDate to string for SQL
    query.bindValue(":prix", prix);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}



// Method to display products from the database
// Method to display products from the database
QSqlQueryModel* Product::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM product");

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
