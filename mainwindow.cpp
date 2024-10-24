#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addemployee.h"
#include "editemployee.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();

    // Load employees into the table view on startup
    loadEmployeeData();

    // Connect Add and Remove buttons to their respective slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Function to load employee data from the database
void MainWindow::loadEmployeeData()
{
    // Create a new QSqlQueryModel
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Set the SQL query to fetch employee data
    model->setQuery("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, AGE, GENDER, PHONE FROM EMPLOYEE");

    // Check if there was an error in the query
    if (model->lastError().isValid()) {
        qDebug() << "Error loading data from database: " << model->lastError().text();
        return;
    }

    // Set the model to the QTableView to display the data
    ui->tableView->setModel(model);

    // Resize the columns to fit the data
    ui->tableView->resizeColumnsToContents();
}
// Slot to open the AddEmployeeDialog when the Add button is clicked
void MainWindow::on_addButton_clicked()
{
    // Create and open the AddEmployeeDialog
    AddEmployee addEmployeeDialog(this);

    if (addEmployeeDialog.exec() == QDialog::Accepted) {
        // If dialog was accepted, add the employee to the database
        addEmployeeDialog.addEmployeeToDatabase();

        // Reload the employee data to show the new entry
        loadEmployeeData();
    }
}

// Slot to handle removing an employee
void MainWindow::on_removeButton_clicked()
{
    // Get the selected row from the table
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.size() > 0) {
        int row = selectedRows[0].row();
        QString cinemp = ui->tableView->model()->index(row, 0).data().toString();  // Get the CINEMP of the selected employee

        // Create an SQL query to remove the selected employee by CINEMP
        QSqlQuery query;
        query.prepare("DELETE FROM EMPLOYEE WHERE CINEMP = :cinemp");
        query.bindValue(":cinemp", cinemp);

        // Execute the query and check if it was successful
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Employee removed successfully.");
            loadEmployeeData();  // Reload the employee data after removing
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove employee: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No employee selected for removal.");
    }
}
void MainWindow::on_editButton_clicked()
{
    // Get the selected row from the table
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.size() > 0) {
        int row = selectedRows[0].row();
        QString cinemp = ui->tableView->model()->index(row, 0).data().toString();  // Get the CINEMP of the selected employee

        // Fetch the selected employee's data from the database
        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYEE WHERE CINEMP = :cinemp");
        query.bindValue(":cinemp", cinemp);

        if (query.exec() && query.next()) {
            // Pass the employee data to the EditEmployeeDialog
            EditEmployee editEmployeeDialog(this);

            editEmployeeDialog.setEmployeeData(query.value("CINEMP").toString(),
                                               query.value("IDEMP").toString(),
                                               query.value("FULL_NAME").toString(),
                                               query.value("HIRE_DATE").toDate(),
                                               query.value("ROLE").toString(),
                                               query.value("SALARY").toDouble(),
                                               query.value("EMAIL").toString(),
                                               query.value("AGE").toInt(),
                                               query.value("GENDER").toString(),
                                               query.value("PHONE").toString());

            if (editEmployeeDialog.exec() == QDialog::Accepted) {
                // If dialog was accepted, update the employee in the database
                editEmployeeDialog.updateEmployeeInDatabase();

                // Reload the employee data to reflect the changes
                loadEmployeeData();
            }
        } else {
            QMessageBox::warning(this, "Error", "Failed to retrieve employee data: " + query.lastError().text());
        }
    } else {
        QMessageBox::warning(this, "Error", "No employee selected for editing.");
    }
}
