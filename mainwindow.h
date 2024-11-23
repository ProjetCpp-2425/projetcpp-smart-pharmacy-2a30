#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlQuery>

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
    void on_imageButton_clicked();
    void onSortButtonClicked();
    void on_logoutButton_clicked();
    void generatePdf();
    void on_loadButton_clicked();
    void onTableSelectionChanged();
private:
    Ui::MainWindow *ui;  // UI pointer
    QString userRole;
    void setupRoleBasedAccess();
    QMap<QString, QString> imagePaths;
};

#endif // MAINWINDOW_H
