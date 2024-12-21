#ifndef DIALOGMODIFIER_H
#define DIALOGMODIFIER_H

#include "ventes.h"
#include <QDialog>

namespace Ui {
class Dialogmodifier;
}

class Dialogmodifier : public QDialog
{
    Q_OBJECT

public:
    // Constructor that accepts the sale ID (ID_VENTE) and loads the sale data
    explicit Dialogmodifier(QWidget *parent = nullptr, int ID_VENTE = -1);
    ~Dialogmodifier();

    // Set the sale ID
    void setIdVente(int ID_VENTE);

signals:
    void VenteModified();  // Signal emitted when the sale is modified

private slots:
    // Slot to handle Modify button click
    void on_pushButton_Modifier_clicked();
    // Slot to handle Cancel button click
    void on_pushButton_Annuler_clicked();

private:
    Ui::Dialogmodifier *ui;
    int ID_VENTE;  // Sale ID to identify the sale to modify

    // Method to load the sale data into the dialog fields
    void loadVenteData(int ID_VENTE);
};

#endif // DIALOGMODIFIER_H
