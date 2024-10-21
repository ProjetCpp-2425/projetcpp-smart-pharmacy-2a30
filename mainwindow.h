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
    // Function to load employee data from the database
    void loadEmployeeData();

    // Slot for adding employee (this will open the dialog)
    void on_addButton_clicked();

    // Slot for removing employee
    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;  // UI pointer
};

#endif // MAINWINDOW_H
