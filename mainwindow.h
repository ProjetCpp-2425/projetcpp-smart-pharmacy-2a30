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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadEmployeeData();
    void on_statistique_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_searchButton_clicked();
    void on_editButton_clicked();

    void onSortButtonClicked();

    void generatePdf();
    void on_loadButton_clicked();
private:
    Ui::MainWindow *ui;  // UI pointer
};

#endif // MAINWINDOW_H
