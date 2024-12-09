#include "historiquedialog.h"
#include "ui_historiquedialog.h"
#include <QFileDialog>


HistoriqueDialog::HistoriqueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoriqueDialog) {
    ui->setupUi(this);
}

HistoriqueDialog::~HistoriqueDialog() {
    delete ui;
}

void HistoriqueDialog::loadHistorique() {
    QSqlQueryModel *model = ventes.getHistorique();

    if (model) {
        ui->tableView->setModel(model); // Display data in a table view
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de charger l'historique des ventes."));
    }
}


void HistoriqueDialog::on_exportButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (filePath.isEmpty()) return;

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Arial", 12));

    painter.drawText(100, 100, "Historique des Ventes");

    int yOffset = 150;
    QAbstractItemModel *model = ui->tableView->model();

    if (!model) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucune donnée à exporter."));
        return;
    }

    for (int row = 0; row < model->rowCount(); ++row) {
        QString rowData;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowData += model->data(model->index(row, col)).toString() + " ";
        }
        painter.drawText(50, yOffset, rowData);
        yOffset += 50;
    }

    painter.end();
    QMessageBox::information(this, tr("Succès"), tr("Historique exporté avec succès."));
}

void HistoriqueDialog::on_Load_clicked()
{
      loadHistorique();
}

