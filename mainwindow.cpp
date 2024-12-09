#include "mainwindow.h"
#include <QCompleter>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include "qprocess.h"
#include <QPainter>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "dialogmodifier.h"
#include <QtCharts/QPieSeries>
#include <QChart>
#include <QChartView>
#include <QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextStream>
#include <QMessageBox>
#include <QAuthenticator>
#include <QEventLoop>
#include <QRegularExpression>
#include "ventes.h"
#include "dashboarddialog.h"
#include "historiquedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("SALES");
    model->select();
    ui->tableView->setModel(Etmp.afficher());
    setupVentesStatsChart();

    connect(ui->pushButton_Modifier, &QPushButton::clicked, this, &MainWindow::on_pushButton_Modifier_clicked);
    connect(ui->refresh, &QPushButton::clicked, this, &::MainWindow::on_refresh_Clicked);

 }



MainWindow::~MainWindow() {

}
QSqlQueryModel* MainWindow::getventesStats() {
    QSqlQueryModel *model = new QSqlQueryModel;

    // Query to calculate total QUANTITE for each CODEMEDIC
    model->setQuery("SELECT CODEMEDIC, SUM(QUANTITE) as TOTAL_QUANTITE FROM SALES GROUP BY CODEMEDIC;");

    if (model->rowCount() == 0) {
        qDebug() << "No data found for QUANTITE stats!";
    } else {
        qDebug() << "Data found!";
    }

    return model;
}


bool MainWindow::setupVentesStatsChart() {
    QSqlQueryModel* model = getventesStats();

    if (model->rowCount() == 0) {
        qDebug() << "No ventes statistics available!";
        return false;  // Retourne false si aucune donnée n'est disponible
    }

    // Crée une série de barres pour le graphique
    QBarSeries *barSeries = new QBarSeries();

    // Vecteurs pour stocker les QBarSet et les catégories des postes
    QVector<QBarSet*> barSets;
    QVector<QString> categories;

    // Parcourt les données pour créer les ensembles de barres
    for (int row = 0; row < model->rowCount(); ++row) {
        QString code = model->data(model->index(row, 0)).toString();
        int quantite = model->data(model->index(row, 1)).toInt();

        // Crée un QBarSet pour chaque poste
        QBarSet *set = new QBarSet(code);
        *set << quantite;
        barSets.append(set);
        categories.append(code);
    }

    // Ajoute les ensembles de barres à la série
    for (QBarSet *set : barSets) {
        barSeries->append(set);
    }

    // Crée le graphique et configure ses propriétés
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Number of medic per code");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("quantite");
    axisY->setRange(0, 100);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    // Ajoute les axes au graphique
    chart->addAxis(axisX, Qt::AlignBottom);  // Ajouter un axe X au graphique
    chart->addAxis(axisY, Qt::AlignLeft);    // Ajouter un axe Y au graphique
    barSeries->attachAxis(axisX);             // Attacher l'axe X à la série
    barSeries->attachAxis(axisY);             // Attacher l'axe Y à la série

    // Crée la vue du graphique et active l'anticrénelage
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoie le contenu existant de l'onglet avant d'ajouter le nouveau graphique
    QLayout *oldLayout = ui->tab_4->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Supprime les widgets
            delete item;  // Supprime les items
        }
        delete oldLayout;
    }

    // Ajoute le nouveau graphique au layout de l'onglet
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->tab_4->setLayout(layout);

    return true;  // Retourne true si le graphique est correctement mis à jour
}

void MainWindow::on_refresh_Clicked() {
    qDebug() << "Refreshing statistics...";
    // Appeler la fonction de mise à jour des statistiques
    bool success = setupVentesStatsChart();

        if (success) {
            QMessageBox::information(this, "Rafraîchissement", "Les statistiques ont été mises à jour avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la mise à jour des statistiques. Veuillez réessayer.");
        }
    }
void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupération des valeurs des champs
    int ID_VENTE = ui->id_vente->text().toInt();
    float PRIX = ui->PRIX->text().toFloat();
    int QUANTITE = ui->quantite->text().toInt();
    float TOTALTHT = ui->total->text().toFloat();
    QString CODEMEDIC = ui->codemedic->text();
    QString DESIGNIATION = ui->designiation->text();
    QDate SDATE = ui->date->date();

    // Contrôles de saisie
    if (ID_VENTE<=0 || PRIX<=0 || QUANTITE<1 || TOTALTHT<0 || DESIGNIATION.isEmpty() || CODEMEDIC.isEmpty() || SDATE.isNull()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("Veuillez remplir tous les champs obligatoires ."), QMessageBox::Ok);
        return;
    }

    // Vérification que l'ID est un entier positif
    if (ID_VENTE <= 0) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("L'ID doit être un entier positif."), QMessageBox::Ok);
        return;
    }
    if (PRIX <= 0) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("PRIX doit être un REEL positif."), QMessageBox::Ok);
        return;
    }

    // Vérification que l'âge est supérieur à 18
    if (QUANTITE < 1) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur d'âge"), QObject::tr("QUANTITE INVALIDE."), QMessageBox::Ok);
        return;
    }


    // Création de l'employé
    Ventes v(ID_VENTE, QUANTITE, PRIX,TOTALTHT, CODEMEDIC, DESIGNIATION, SDATE);

        // Attempt to add the sale
        bool test = v.ajouter();
        if (test) {
            QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("The sale has been added successfully."), QMessageBox::Ok);
            ui->tableView->setModel(v.afficher());  // Refresh the view
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to add the sale. Check the data or the database connection."), QMessageBox::Ok);
        }
    }
void MainWindow::on_pushButton_supprimer_clicked()
{
    int ID_VENTE = ui->lineEdit_ID->text().toInt(); // Assuming lineEdit_ID is where the Sale ID is entered

    // Create a Ventes object and attempt to delete the sale with the specified ID
    Ventes v;
    bool test = v.supprimer(ID_VENTE); // Attempt to delete the sale

    // Check the result of the deletion and display appropriate message
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("The sale has been successfully deleted."), QMessageBox::Ok);
        ui->tableView->setModel(v.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to delete the sale. Please check the ID or database connection."), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    // Retrieve the sale ID from the lineEdit (assuming the sale ID is entered in a QLineEdit)
    int ID_VENTE = ui->lineEdit_ID->text().toInt();

    if (ID_VENTE <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez entrer un ID de vente valide."));
        return;
    }

    // Create and open the modification dialog for the given sale ID
    Dialogmodifier *dialog = new Dialogmodifier(this, ID_VENTE);
    connect(dialog, &Dialogmodifier::VenteModified, this, &MainWindow::onventeModified);
    dialog->exec();
}

void MainWindow::onventeModified()
{
    // Refresh or update the view after a sale modification
    ui->tableView->setModel(Etmp.afficher());
    QMessageBox::information(this, tr("Succès"), tr("La vente a été modifiée avec succès."));
}

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    QSqlQueryModel *searchModel = Etmp.chercher(arg1); // Call the chercher method with user input
    if (searchModel != nullptr) {
        ui->tableView->setModel(searchModel); // Update the table view with search results
    } else {
        // Clear the table if no results are found
        ui->tableView->setModel(nullptr);
    }
}


void MainWindow::on_tri_clicked()
{
    QString critere = ui->comboBoxTri->currentText(); // Get the selected sorting criteria
    QSqlQueryModel *model = Etmp.trier(critere); // Call the `trier` method of the `Ventes` class

    if (model) {
        ui->tableView->setModel(model); // Update the table view with the sorted model
        QMessageBox::information(this, tr("Tri"), tr("Les résultats ont été triés avec succès."));
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de trier les résultats."));
    }
}

void MainWindow::on_resetButton_clicked() {
    // Create a new query model to retrieve all data without filters or sorting
    QSqlQueryModel *model = new QSqlQueryModel();

    // Query to retrieve all sales records without any sorting or filtering
    QString queryStr = "SELECT * FROM SALES"; // Replace with your actual table name if different
    QSqlQuery query;

    if (query.exec(queryStr)) {
        model->setQuery(std::move(query));  // Use move to avoid copying
        // Update the table view with the unfiltered results
        ui->tableView->setModel(model); // Apply the model to the table view
        QMessageBox::information(this, tr("Réinitialisation"), tr("La vue a été réinitialisée."));
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de réinitialiser la vue."));
        qDebug() << "Erreur de réinitialisation : " << query.lastError();
    }
}


void MainWindow::on_exporterEnPDF_clicked()
{
    // Choose file path to save the PDF
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save as PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (filePath.isEmpty()) {
        return;  // User canceled
    }

    // Create the QPdfWriter object
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);  // Set resolution

    // Set up QPainter to write to the PDF
    QPainter painter(&pdfWriter);
    QFont font("Arial", 12);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Title
    painter.drawText(100, 100, "Liste des ventes");

    int yOffset = 150;  // Initial Y position for data
    int i = 1;  // Sale count

    // Execute the query to retrieve sales
    QSqlQuery query;
    if (!query.exec("SELECT * FROM SALES")) {
        QMessageBox::warning(this, tr("Query Error"), tr("Failed to execute query. Error: %1").arg(query.lastError().text()));
        return;
    }

    // Iterate over each sale and write details in a structured format
    while (query.next()) {
        // Sale header
        painter.drawText(50, yOffset, "Vente " + QString::number(i) + ":");
        i++;  // Increment count
        yOffset += 70;

        // Print each attribute
        painter.drawText(100, yOffset, "ID Vente: " + query.value("ID_VENTE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Prix: " + query.value("PRIX").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Code Médicament: " + query.value("CODEMEDIC").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Désignation: " + query.value("DESIGNIATION").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Quantité: " + query.value("QUANTITE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Total HT: " + query.value("TOTALHT").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Date: " + query.value("SDATE").toString());

        // Add some space between each sale
        yOffset += 140;
    }

    // Finalize the PDF
    painter.end();

    QMessageBox::information(this, tr("Exportation réussie"), tr("Le fichier PDF a été généré avec succès."));
}
void MainWindow::on_dashboardButton_clicked() {
    DashboardDialog *dashboardDialog = new DashboardDialog(this);
    dashboardDialog->exec();  // Open the dialog modally
    delete dashboardDialog;   // Clean up after closing
}


void MainWindow::on_Historique_clicked()
{
    HistoriqueDialog *dialog = new HistoriqueDialog(this);
    dialog->exec();
}

