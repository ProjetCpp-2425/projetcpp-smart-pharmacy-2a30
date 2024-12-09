#ifndef HISTORIQUEDIALOG_H
#define HISTORIQUEDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include "ventes.h" // Include your Ventes class header

namespace Ui {
class HistoriqueDialog;
}

class HistoriqueDialog : public QDialog {
    Q_OBJECT

public:
    explicit HistoriqueDialog(QWidget *parent = nullptr);
    ~HistoriqueDialog();

private slots:
    void loadHistorique();
    void on_loadButton_clicked();
    void on_exportButton_clicked();

    void on_Load_clicked();

private:
    Ui::HistoriqueDialog *ui;
    Ventes ventes; // Instance of your Ventes class
};

#endif // HISTORIQUEDIALOG_H
