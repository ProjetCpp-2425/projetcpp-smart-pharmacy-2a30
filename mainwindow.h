#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTableWidget>
#include <QMainWindow>
#include<QSqlDatabase>
#include<supplier.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void connectToDatabase();
   //QVector<Transaction> getTransactions();

   // QList<Transaction> *executeQuery(QString request);
    //QString escapeCsvValue(const QString &value);
    //QString exportTableToexcel(QTableWidget* table);
    //QList<int>* getTransactionYears(QVector<Transaction> transactions);
    //Statistics fillStatestics(QVector<Transaction> transactions,int year);
    // void updateChart();
   void getSupplier();






private slots:
   // void on_typeRecord_currentIndexChanged(int index);


   // void on_pushButton_17_clicked();

  //  void on_listTransaction_cellDoubleClicked(int row, int column);

   // void on_typeRecord_2_currentIndexChanged(int index);

   // void on_typeRecord_2_currentTextChanged(const QString &arg1);



   // void on_pushButton_15_clicked();

    //void on_pushButton_2_clicked();

    //void on_widget_16_customContextMenuRequested(const QPoint &pos);

   // void on_lineEdit_textChanged(const QString &arg1);

    //void on_date_Search_textChanged(const QString &arg1);

    //void on_search_id_textChanged(const QString &arg1);

   void on_add_supplier_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
