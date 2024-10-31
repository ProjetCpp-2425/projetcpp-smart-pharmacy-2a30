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
    // Function to load supplier data from the database
    void loadSupplierData();

    // Slot for adding supplier (this will open the dialog)
    void on_addButton_clicked();

    // Slot for removing supplier
    void on_removeButton_clicked();

    // Slot for editing supplier (this will open the edit dialog)
    void on_editButton_clicked();  // New function for Edit button click

private:
    Ui::MainWindow *ui;  // UI pointer
};

#endif // MAINWINDOW_H
