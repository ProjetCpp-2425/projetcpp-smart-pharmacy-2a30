#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ventes.h"
#include <QMainWindow>
#include <QCompleter>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>

#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlQueryModel>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_Modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_chercher_textChanged(const QString &arg1);
    void on_tri_clicked();
    void on_resetButton_clicked();
    void on_exporterEnPDF_clicked();
    bool setupVentesStatsChart();
    void on_refresh_Clicked();
      // Reject button clicked
    void onventeModified();
    void on_dashboardButton_clicked();
    void on_historiqueButton_clicked();




    void on_Historique_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel* getventesStats();
    Ventes Etmp;
     bool validerSaisie();

    //new

};






#endif // MAINWINDOW_H
