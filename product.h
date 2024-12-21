#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>  // Include QDate for date handling

class Product {
private:
    int id_pro;              // Product ID
    QDate date_comm;         // Date of the command
    float montant_total;     // Total amount
    QString status;          // Status
    int quantite;            // Quantity
    QDate date_expiration;   // Expiration date
    float prix;              // Price

public:
    // Constructors
    Product();  // Default constructor
    Product(int id, QDate date, float montant, QString stat, int quantite, QDate expirationDate, float price);  // Parameterized constructor

    // Method to add a product to the database
    bool ajouter();

    // Method to display products from the database
    QSqlQueryModel* afficher();

    // Method to delete a product from the database by ID
    bool supprimer(int id);

    // Method to calculate the total profit for a product
    float calculateProfit() const;

    // Method to find the most profitable product
    static Product findMostProfitableProduct();

    // Getters and Setters
    int getIdPro() const { return id_pro; }
    void setIdPro(int id) { id_pro = id; }

    QDate getDateComm() const { return date_comm; }
    void setDateComm(QDate date) { date_comm = date; }

    float getMontantTotal() const { return montant_total; }
    void setMontantTotal(float montant) { montant_total = montant; }

    QString getStatus() const { return status; }
    void setStatus(QString stat) { status = stat; }

    int getQuantite() const { return quantite; }
    void setQuantite(int quantite) { this->quantite = quantite; }

    QDate getDateExpiration() const { return date_expiration; }
    void setDateExpiration(QDate expirationDate) { date_expiration = expirationDate; }

    float getPrix() const { return prix; }
    void setPrix(float price) { prix = price; }

    QSqlQueryModel* modifier(const QString &searchTerm);
};

#endif // PRODUCT_H
