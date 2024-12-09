#include "dialogmodifier.h"
#include "ui_dialogmodifier.h"
#include <QMessageBox>

// Constructor that accepts the sale ID (ID_VENTE) and loads the sale data
Dialogmodifier::Dialogmodifier(QWidget *parent, int ID_VENTE) :
    QDialog(parent),
    ui(new Ui::Dialogmodifier),
    ID_VENTE(ID_VENTE)  // Initialize the sale ID
{
    ui->setupUi(this);
    loadVenteData(ID_VENTE);  // Load the sale data using the ID
    connect(ui->Modifier, &QPushButton::clicked, this, &Dialogmodifier::on_pushButton_Modifier_clicked);
    connect(ui->Annuler, &QPushButton::clicked, this, &Dialogmodifier::on_pushButton_Annuler_clicked);
}

// Destructor to clean up
Dialogmodifier::~Dialogmodifier()
{
    delete ui;
}

// Set the sale ID
void Dialogmodifier::setIdVente(int ID_VENTE)
{
    this->ID_VENTE = ID_VENTE;
    loadVenteData(ID_VENTE);  // Load the sale data after setting the ID
}

// Load the sale data into the dialog fields
void Dialogmodifier::loadVenteData(int ID_VENTE)
{
    Ventes v;
    bool found = v.loadVentesdata(ID_VENTE);  // Load sale data using the ID

    if (!found) {
        QMessageBox::critical(this, tr("Erreur"), tr("Vente non trouvée"));
        return;
    }

    // Assuming the `Ventes` class has getters for each field
    ui->PRIX_3->setText(QString::number(v.getPRIX()));
    ui->quantite_3->setText(QString::number(v.getQUANTITE()));
    ui->total_3->setText(QString::number(v.getTOTALHT()));
    ui->codemedic_3->setText(v.getCode());
    ui->designiation_3->setText(v.getDESIGNIATION());
    ui->date_3->setDate(v.getSDATE());
}

void Dialogmodifier::on_pushButton_Modifier_clicked()
{
    // Extract values from UI
    float PRIX = ui->PRIX_3->text().toFloat();
    int QUANTITE = ui->quantite_3->text().toInt();
    float TOTALHT = ui->total_3->text().toFloat();
    QString CODEMEDIC = ui->codemedic_3->text();
    QString DESIGNIATION = ui->designiation_3->text();
    QDate SDATE = ui->date_3->date();

    // Retrieve current sale data
    Ventes v;
    bool found = v.loadVentesdata(ID_VENTE);

    if (!found) {
        QMessageBox::critical(this, tr("Erreur"), tr("Vente non trouvée."));
        return;
    }

    // Update fields with new values
    if (PRIX >= 0) v.setPRIX(PRIX);
    if (QUANTITE >= 0) v.setQUANTITE(QUANTITE);
    if (TOTALHT >= 0) v.settotal(TOTALHT);
    if (!CODEMEDIC.isEmpty()) v.setcode(CODEMEDIC);
    if (!DESIGNIATION.isEmpty()) v.setDESIGNIATION(DESIGNIATION);
    v.setDATE(SDATE);

    // Save the updated sale information
    if (v.modifier(ID_VENTE)) {
        QMessageBox::information(this, tr("Succès"), tr("Vente modifiée avec succès."));
        close();  // Close the dialog
        emit VenteModified();  // Emit signal indicating the sale was modified
    } else {
        QMessageBox::critical(this, tr("Échec"), tr("Échec de la modification de la vente."));
    }
}

// Slot for handling the "Cancel" button click
void Dialogmodifier::on_pushButton_Annuler_clicked()
{
    close();  // Close the dialog without modifying the sale
}
