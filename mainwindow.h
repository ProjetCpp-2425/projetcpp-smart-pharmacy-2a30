#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSerialPort>
#include <QSerialPortInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &role = "");
    ~MainWindow();

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
    void readSerialData();           // Slot to handle serial data
private:
    Ui::MainWindow *ui;  // UI pointer
    QString userRole;
    QString buffer;
    void setupRoleBasedAccess();
    QMap<QString, QString> imagePaths;
    QSerialPort *serialPort;         // Serial port instance
    QDialog *waitingDialog;          // Dialog for waiting on token scan
    void saveTokenToDatabase(const QString &uid, const QString &employeeID); // Save token to database
};

#endif // MAINWINDOW_H
