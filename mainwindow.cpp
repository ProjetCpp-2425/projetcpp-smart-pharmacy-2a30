#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addemployee.h"
#include "editemployee.h"
#include "employee.h"  // Include Employee for the calculateAge function
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>
#include <QStandardItemModel>
// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("PHARMEASE - Dashboard");
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();

    // Load employees into the table view on startup
    loadEmployeeData();

    // Connect Add and Remove buttons to their respective slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
    connect(ui->generatePdfButton, &QPushButton::clicked, this, &MainWindow::generatePdf);
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Function to load employee data from the database
void MainWindow::loadEmployeeData()
{
    QSqlQuery query;
    query.prepare("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE FROM EMPLOYEE");

    if (!query.exec()) {
        qDebug() << "Error loading data from database: " << query.lastError().text();
        return;
    }

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"CINEMP", "IDEMP", "FULL NAME", "HIRE DATE", "ROLE", "SALARY", "EMAIL", "AGE", "GENDER", "PHONE"});

    while (query.next()) {
        QList<QStandardItem *> rowItems;
        rowItems << new QStandardItem(query.value("CINEMP").toString());
        rowItems << new QStandardItem(query.value("IDEMP").toString());
        rowItems << new QStandardItem(query.value("FULL_NAME").toString());
        rowItems << new QStandardItem(query.value("HIRE_DATE").toDate().toString("yyyy-MM-dd"));
        rowItems << new QStandardItem(query.value("ROLE").toString());
        rowItems << new QStandardItem(QString::number(query.value("SALARY").toDouble(), 'f', 2));
        rowItems << new QStandardItem(query.value("EMAIL").toString());
        QString dateOfBirthStr = query.value("DATE_OF_BIRTH").toDate().toString("yyyy-MM-dd");
        QDate dateOfBirth = QDate::fromString(dateOfBirthStr, "yyyy-MM-dd");
        int age = Employee::calculateAge(dateOfBirth);
        rowItems << new QStandardItem(QString::number(age));
        rowItems << new QStandardItem(query.value("GENDER").toString());
        rowItems << new QStandardItem(query.value("PHONE").toString());

        model->appendRow(rowItems);
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

// Slot to open the AddEmployee dialog
void MainWindow::on_addButton_clicked()
{
    AddEmployee addEmployeeDialog(this);
    if (addEmployeeDialog.exec() == QDialog::Accepted) {
        loadEmployeeData();  // Reload data after addition
    }
}

// Slot to remove an employee
void MainWindow::on_removeButton_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No employee selected for removal.");
        return;
    }

    QString cinemp = ui->tableView->model()->index(selectedRows[0].row(), 0).data().toString();
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEE WHERE CINEMP = :cinemp");
    query.bindValue(":cinemp", cinemp);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Employee removed successfully.");
        loadEmployeeData();
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove employee: " + query.lastError().text());
    }
}

// Slot to edit an employee
void MainWindow::on_editButton_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No employee selected for editing.");
        return;
    }

    QString cinemp = ui->tableView->model()->index(selectedRows[0].row(), 0).data().toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEE WHERE CINEMP = :cinemp");
    query.bindValue(":cinemp", cinemp);

    if (query.exec() && query.next()) {
        EditEmployee editEmployeeDialog(this);
        editEmployeeDialog.setEmployeeData(
            query.value("CINEMP").toString(),
            query.value("IDEMP").toString(),
            query.value("FULL_NAME").toString(),
            query.value("HIRE_DATE").toDate(),
            query.value("ROLE").toString(),
            query.value("SALARY").toDouble(),
            query.value("EMAIL").toString(),
            query.value("DATE_OF_BIRTH").toDate(),
            query.value("GENDER").toString(),
            query.value("PHONE").toString()
        );

        if (editEmployeeDialog.exec() == QDialog::Accepted) {
            loadEmployeeData();  // Reload data after editing
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to retrieve employee data: " + query.lastError().text());
    }
}
void MainWindow::onSortButtonClicked()
{
    QString selectedOption = ui->comboBox->currentText();
    QString sortColumn;
    QString orderByClause;

    // Determine the sorting column and order based on the selected option
    if (selectedOption == "Salary") {
        sortColumn = "SALARY";
        orderByClause = sortColumn + " DESC";  // Highest salary first
    } else if (selectedOption == "Hire Date") {
        sortColumn = "HIRE_DATE";
        orderByClause = sortColumn + " DESC";  // Most recent date first
    } else if (selectedOption == "Role") {
        orderByClause = "CAST(ROLE AS VARCHAR2(100)) ASC";  // Alphabetical order
    } else if (selectedOption == "Age") {
        sortColumn = "AGE";
        orderByClause = sortColumn + " DESC";  // Oldest employee first
    } else if (selectedOption == "Gender") {
        // Custom sorting: Display females first
        orderByClause = "CASE WHEN CAST(GENDER AS VARCHAR2(1)) = 'F' THEN 0 ELSE 1 END, CAST(GENDER AS VARCHAR2(1)) ASC";
    }

    // Create a new query with ORDER BY to sort
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = QString("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, AGE, GENDER, PHONE FROM EMPLOYEE ORDER BY %1").arg(orderByClause);
    model->setQuery(query);

    // Check for query errors
    if (model->lastError().isValid()) {
        qDebug() << "Error sorting data: " << model->lastError().text();
        return;
    }

    // Set the sorted model to the table view
    ui->tableView->setModel(model);
}
void MainWindow::generatePdf()
{
    // Open a file dialog to select the save location and filename
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));

    // Check if the user canceled the file dialog
    if (fileName.isEmpty()) {
        return;
    }

    // Create a PDF writer object
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    // Create a QPainter to draw on the PDF
    QPainter painter(&pdfWriter);

    // Set font for the PDF
    QFont font("Arial", 12);
    painter.setFont(font);

    // Draw title
    painter.drawText(100, 100, "Employee Data");

    int yOffset = 150; // Initial y position for the data
    int i = 1;
    // Create a query to fetch employee data
    QSqlQuery query("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, AGE, GENDER, PHONE FROM EMPLOYEE");

    // Iterate over each employee and print details in the specified format
    while (query.next()) {
        // Print each employee's data in a structured format
        painter.drawText(50, yOffset, "Employee " + QString::number(i) + ":");
        i++;  // Increment the employee count
        yOffset += 60;
        painter.drawText(100, yOffset, "CINEMP: " + query.value("CINEMP").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "IDEMP: " + query.value("IDEMP").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Full Name: " + query.value("FULL_NAME").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Hire Date: " + query.value("HIRE_DATE").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Role: " + query.value("ROLE").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Salary: " + query.value("SALARY").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Email: " + query.value("EMAIL").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Age: " + query.value("AGE").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Gender: " + query.value("GENDER").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Phone: " + query.value("PHONE").toString());

        // Add some space between employees
        yOffset += 100;
    }

    // Finalize the PDF
    painter.end();

    // Optionally, show a message box to confirm PDF creation
    QMessageBox::information(this, tr("PDF Generated"), tr("The employee data has been saved as a PDF."));
}
