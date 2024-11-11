#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "product.h"
#include <QMessageBox>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlError>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gestion de Produits");  // Set the window title
    ui->oui->setModel(product.afficher());
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Validate input fields
    if (ui->le_id->text().isEmpty() || ui->le_date->text().isEmpty() ||
        ui->le_montant->text().isEmpty() || ui->le_status->text().isEmpty() ||
        ui->le_quantite->text().isEmpty() || ui->le_date_expiration->text().isEmpty() ||
        ui->le_prix->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return; // Exit if any field is empty

    }

    // Retrieve input values
    int id = ui->le_id->text().toInt();
    QString date = ui->le_date->text();
    float montant = ui->le_montant->text().toFloat();
    QString status = ui->le_status->text();
    int quantite = ui->le_quantite->text().toInt();
    QString date_expiration = ui->le_date_expiration->text();
    float prix = ui->le_prix->text().toFloat();

    // Create a Product object with the data
    Product product(id, date, montant, status, quantite, date_expiration, prix);
    bool test = product.ajouter(); // Call the ajouter function

    if (test)
    {
        QMessageBox::information(this, QObject::tr("Success"),
                    QObject::tr("Addition successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->oui->setModel(product.afficher()); // Refresh the table view
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Addition Failed"),
                    QObject::tr("Addition not performed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_sup_clicked()
{
    // Get the ID from the line edit for deletion
    int id = ui->le_sup->text().toInt();

    // Assuming 'product' is the Product object responsible for managing products
    bool test = product.supprimer(id); // Call the supprimer function

    if(test)
    {
        ui->oui->setModel(product.afficher()); // Refresh the table view
        QMessageBox::information(this, QObject::tr("Success"),
                    QObject::tr("Suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Error"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_non_clicked()
{
    // Get the ID from the search field
    QString productId = ui->le_search->text();

    // Verify that the ID is not empty
    if (productId.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez entrer un ID de produit valide dans le champ de recherche.");
        return;
    }

    // Retrieve new values from input fields
    QString newDate = ui->le_date_2->text();
    float newMontant = ui->le_montant_2->text().toFloat();
    QString newStatus = ui->le_status_2->text();
    int newQuantite = ui->le_quantite_2->text().toInt();
    QString newDateExpiration = ui->le_date_expiration_3->text();
    float newPrix = ui->le_prix_2->text().toFloat();

    // Check that fields are not empty
    if (newDate.isEmpty() || newStatus.isEmpty() || newDateExpiration.isEmpty() ||
        ui->le_montant_2->text().isEmpty() || ui->le_quantite_2->text().isEmpty() || ui->le_prix_2->text().isEmpty()) {
        QMessageBox::warning(this, "Modification", "Tous les champs doivent être remplis.");
        return;
    }

    // Prepare the query to update the product in the database
    QSqlQuery query;
    query.prepare("UPDATE product SET DATE_COMM = :date, MONTANT_TOTAL = :montant, status = :status, "
                  "QUANTITE = :quantite, DATE_EXPIRATION = :date_expiration, PRIX = :prix WHERE id_pro = :id");
    query.bindValue(":date", newDate);
    query.bindValue(":montant", newMontant);
    query.bindValue(":status", newStatus);
    query.bindValue(":quantite", newQuantite);
    query.bindValue(":date_expiration", newDateExpiration);
    query.bindValue(":prix", newPrix);
    query.bindValue(":id", productId);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Modification", "Le produit a été modifié avec succès.");
            ui->oui->setModel(product.afficher()); // Refresh the table view
        } else {
            QMessageBox::information(this, "Modification", "Aucun produit trouvé avec cet ID. Vérifiez l'ID.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification dans la base de données : " + query.lastError().text());
    }
}

void MainWindow::on_search_clicked()
{
    // Retrieve the ID from the search field
    QString searchTerm = ui->le_search->text();

    // Check if the field is empty
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID.");
        return;
    }

    // Prepare SQL query to search for the product
    QSqlQuery query;
    query.prepare("SELECT DATE_COMM, MONTANT_TOTAL, STATUS, QUANTITE, DATE_EXPIRATION, PRIX FROM product WHERE id_pro = :id");
    query.bindValue(":id", searchTerm);

    if (query.exec()) {
        if (query.next()) {
            // If the product is found, populate the fields
            ui->le_date_2->setText(query.value(0).toString());
            ui->le_montant_2->setText(query.value(1).toString());
            ui->le_status_2->setText(query.value(2).toString());
            ui->le_quantite_2->setText(query.value(3).toString());
            ui->le_date_expiration_3->setText(query.value(4).toString());
            ui->le_prix_2->setText(query.value(5).toString());
        } else {
            QMessageBox::information(this, "Recherche", "Aucun produit trouvé avec cet ID.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche dans la base de données : " + query.lastError().text());
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->oui->setModel(product.afficher()); // Refresh the table view
}
void MainWindow::on_generatePdfButton_clicked()
{
    // Open a file dialog to select the save location and filename
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));

    // Check if the user canceled the file dialog
    if (fileName.isEmpty()) {
        return;
    }

    // Create a PDF writer object
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    // Create a QPainter to draw on the PDF
    QPainter painter(&pdfWriter);

    // Set font for the PDF
    QFont font("Arial", 12);
    painter.setFont(font);

    // Draw title
    painter.drawText(100, 100, "Product List");

    int yOffset = 150; // Initial y position for the data
    int i = 1;

    // Create a query to fetch product data
    QSqlQuery query("SELECT id_pro, date_comm, montant_total, status, quantite, date_expiration, prix FROM product");

    // Iterate over each product and print details in the specified format
    while (query.next()) {
        // Print each product's data in a structured format
        painter.drawText(50, yOffset, "Product " + QString::number(i) + ":");
        i++;  // Increment the product count
        yOffset += 60;
        painter.drawText(100, yOffset, "ID: " + query.value("id_pro").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Date: " + query.value("date_comm").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Amount: " + query.value("montant_total").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Status: " + query.value("status").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Quantity: " + query.value("quantite").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Expiration Date: " + query.value("date_expiration").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Price: " + query.value("prix").toString());

        // Add some space between products
        yOffset += 100;

        // Check if yOffset goes beyond the page size and create a new page if necessary
        if (yOffset > pdfWriter.height() - 100) {
            pdfWriter.newPage();
            yOffset = 150; // Reset yOffset to start from the top of the new page
        }
    }

    // Finalize the PDF
    painter.end();

    // Optionally, show a message box to confirm PDF creation
    QMessageBox::information(this, tr("PDF Generated"), tr("The product data has been saved as a PDF."));
}
