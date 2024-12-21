#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ordonnance.h"
#include "qtablewidget.h"
#include "supplier.h"
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSerialPort>
#include <QSerialPortInfo>
//integration vente produit :
#include "conge.h"
#include "ventes.h"
#include "product.h"
#include <QMainWindow>
#include <QCompleter>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include <QSystemTrayIcon>
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
#include "arduino.h"
#include <QSerialPort>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &role = "");
    ~MainWindow();
    void connectToDatabase();
    void getSupplier();
     QList<Supplier> *executeQuery(QString request);
     QString exportTableToPDF(QTableWidget* table);
     void update_champ_de_recherche_aruino();


private slots:
    void loadEmployeeData();
    void on_statistique_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_searchButton_clicked();
    void on_editButton_clicked();
    void onSortButtonClicked();
    void on_logoutButton_clicked();
    void generatePdf();
    void on_loadButton_clicked();
    void onTableSelectionChanged();
    void on_tokenButton_clicked();    // Slot for token button
    void readSerialData();
    //supplier :
    void on_add_supplier_clicked();
    void on_qrcodegen_clicked();
    void   envoyerSMS(const QString &destinataire, const QString &message);
    void  populateSupplierList();
    void on_SMS_clicked();

    void on_sort_clicked();

    void on_chercher_id_textChanged(const QString &arg1);

    void on_exportsup_clicked();
    // Slot to handle serial data
    //alee :
    void on_pushButton_7_clicked();
    //void loadOrdonnanceData();
    void on_ajouter_produit_2_clicked();

    void on_Modifier_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void rechercheDynamique();

    void on_Trier_2_clicked();

    void on_pushButton_4_clicked();

    void on_sendChatBtn_clicked();

    void on_Retour_clicked();

    void on_chatBot_3_clicked();

    void on_Statistique_4_clicked();

    void on_Statistique_3_clicked();

    void on_RetourS_2_clicked();
    void Supprimer_Histo(int Id);
    void Modifier_Histo(int Id);
    void Ajouter_Histo(int Id);
    void logHistory(const QString &message);

    //integration vente et produit :
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
    //void on_historiqueButton_clicked();

    void on_pushButton_clicked();
    void on_sup_clicked();
    void on_non_clicked();
    void on_search_clicked();
    void on_pushButton_3_clicked();
    void on_generatePdfButton_clicked();
    void on_calendarWidget_clicked(const QDate &date);
    void on_noti_clicked();
    void on_comboBox_activated(int index);
    //void readFromSerial();



    void goToEmployeePage();
    void goToSalesMedsPage();
    void goToSupplierPage();
    void goToOtherPages();
    void on_Historique_clicked();

private:
    Ui::MainWindow *ui;  // UI pointer
    QString userRole;
    QString buffer;
    void setupRoleBasedAccess();
    QMap<QString, QString> imagePaths;
    QSerialPort *serialPort;         // Serial port instance
    QDialog *waitingDialog;          // Dialog for waiting on token scan
    void saveTokenToDatabase(const QString &uid, const QString &employeeID); // Save token to database
    Ordonnance Etmp;
    Ordonnance ord;
    QSqlQueryModel* getventesStats();
    Ventes Etmp1;
     bool validerSaisie();
     conge c;
    void checkProfitNotification(float profit);
    float currentProfit = 0;
    Product product;
    Arduino A;
     QSerialPort *serial;
};

#endif // MAINWINDOW_H
