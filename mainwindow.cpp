#include "mainwindow.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "ui_mainwindow.h"
#include "addemployee.h"
#include "editemployee.h"
#include "employee.h"  // Include Employee for the calculateAge function
#include "login.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVariant>
#include <QStandardItemModel>
#include <QRegularExpressionValidator>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFile>
//integration alee :
#include "mainwindow.h"
#include "ordonnance.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPdfWriter>
#include "QPainter"
#include <QDate>
#include <QSqlError>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QFile>
//integratiion supplier :
#include <supplier.h>
#include <QtSql/QSqlDatabase>
#include <string>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <list>
#include <supplier.h>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <supplier.h>
#include <QtSql/QSqlDatabase>
#include <string>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <list>
#include <supplier.h>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QMenu>
#include <QtCharts/QPieSeries>
#include <QVector>
#include <QVBoxLayout>
#include <iostream>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QCoreApplication>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QDebug>
 #include "qrcodegen.hpp"  // Inclure la bibliothèque qrcodegen

//integration vente et produit :
#include "mainwindow.h"
#include <QCompleter>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include "qprocess.h"
#include <QPainter>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "dialogmodifier.h"
#include <QtCharts/QPieSeries>
#include <QChart>
#include <QChartView>
#include <QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextStream>
#include <QMessageBox>
#include <QAuthenticator>
#include <QEventLoop>
#include <QRegularExpression>
#include <QSystemTrayIcon>
#include "ventes.h"
#include "dashboarddialog.h"
#include "historiquedialog.h"
#include "product.h"
#include "arduino.h"
#include <QSerialPort>
// Constructor
MainWindow::MainWindow(QWidget *parent, const QString &role) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    userRole(role)
{
    ui->setupUi(this);
    this->setWindowTitle("PHARMEASE - Dashboard");
    QSqlDatabase db = QSqlDatabase::database();
    QSqlTableModel *model = new QSqlTableModel(this, db);
    qDebug() << "User role received in MainWindow:" << userRole;
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();
    setupRoleBasedAccess();
    // Load employees into the table view on startup
    loadEmployeeData();
    //arduino
    serialPort = new QSerialPort(this);
    serialPort->setPortName("COM3"); // Replace with your Arduino's COM port
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open serial port:" << serialPort->errorString();
    } else {
        qDebug() << "Serial port opened successfully!";
    }
    populateSupplierList();
    // Connect the serial port's readyRead signal to the slot
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    // Connect Add and Remove buttons to their respective slots
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
    connect(ui->generatePdfButton, &QPushButton::clicked, this, &MainWindow::generatePdf);
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statistique_clicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);
    connect(ui->logoutButton1, &QPushButton::clicked, this, &MainWindow::on_logoutButton_clicked);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTableSelectionChanged);
    connect(ui->tokenbutton, &QPushButton::clicked, this, &MainWindow::on_tokenButton_clicked);

//alee :
    Ordonnance o ;
    ui->tableView_3->setModel(o.display()); // Rafraîchissement de la vue
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();
    // Dans le constructeur de MainWindow
    connect(ui->tableView_3, &QTableView::clicked, this, &MainWindow::on_tableView_clicked);
    connect(ui->idLineEdit_2, &QLineEdit::textChanged, this, &MainWindow::rechercheDynamique);
    connect(ui->ReferenceLineEdit_2, &QLineEdit::textChanged, this, &MainWindow::rechercheDynamique);
//vente et produit :
    model->setTable("SALES");
    model->select();
    ui->tableView_vente->setModel(Etmp1.afficher());
    setupVentesStatsChart();

    connect(ui->pushButton_Modifier, &QPushButton::clicked, this, &MainWindow::on_pushButton_Modifier_clicked);
    connect(ui->refresh, &QPushButton::clicked, this, &::MainWindow::on_refresh_Clicked);
//menu bar!! :
    connect(ui->employeebutton, &QPushButton::clicked, this, &MainWindow::goToEmployeePage);
    connect(ui->salesmeds_2, &QPushButton::clicked, this, &MainWindow::goToSalesMedsPage);
    connect(ui->supplierbutton, &QPushButton::clicked, this, &MainWindow::goToSupplierPage);
    connect(ui->ordonnancebutton, &QPushButton::clicked, this, &MainWindow::goToOtherPages);

    connect(ui->employeebutton1, &QPushButton::clicked, this, &MainWindow::goToEmployeePage);
    connect(ui->medsbutton1, &QPushButton::clicked, this, &MainWindow::goToSalesMedsPage);
    connect(ui->supplierbutton1, &QPushButton::clicked, this, &MainWindow::goToSupplierPage);
    connect(ui->ordonnancebutton2, &QPushButton::clicked, this, &MainWindow::goToOtherPages);

    connect(ui->employeebutton2, &QPushButton::clicked, this, &MainWindow::goToEmployeePage);
    connect(ui->salesmeds, &QPushButton::clicked, this, &MainWindow::goToSalesMedsPage);
    connect(ui->supplierbutton2, &QPushButton::clicked, this, &MainWindow::goToSupplierPage);
    connect(ui->ordonnancebutton_2, &QPushButton::clicked, this, &MainWindow::goToOtherPages);

    connect(ui->employeebutton2_2, &QPushButton::clicked, this, &MainWindow::goToEmployeePage);
    connect(ui->salesmeds_3, &QPushButton::clicked, this, &MainWindow::goToSalesMedsPage);
    connect(ui->supplierbutton2_2, &QPushButton::clicked, this, &MainWindow::goToSupplierPage);
    connect(ui->ordonnancebutton_3, &QPushButton::clicked, this, &MainWindow::goToOtherPages);
}
// Destructor
MainWindow::~MainWindow()
{
    if (serialPort) {
            serialPort->close();
            delete serialPort;
        }
    delete ui;
}
void MainWindow::goToEmployeePage() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->employeepage));
}

void MainWindow::goToSalesMedsPage() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->salesmedspage));
}

void MainWindow::goToSupplierPage() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->supplierpage));
}

void MainWindow::goToOtherPages() {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->otherpages));
}

void MainWindow::on_tokenButton_clicked() {
    // Ensure a row is selected in the table view
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Error", "No employee selected. Please select an employee first.");
        return;
    }

    // Show the "Waiting for Token" dialog
    waitingDialog = new QDialog(this);
    waitingDialog->setWindowTitle("Waiting for Token");
    QLabel *label = new QLabel("Please scan the token...", waitingDialog);
    QVBoxLayout *layout = new QVBoxLayout(waitingDialog);
    layout->addWidget(label);
    waitingDialog->setLayout(layout);
    waitingDialog->resize(200, 100);
    waitingDialog->show();

    qDebug() << "Waiting for token scan...";
}
void MainWindow::readSerialData() {
    // Append incoming data to the buffer
    buffer.append(QString::fromUtf8(serialPort->readAll()));

    // Check if the buffer contains a complete UID (terminated by \n)
    if (buffer.contains("\n")) {
        // Extract the UID by trimming whitespace and newline
        QString uid = buffer.left(buffer.indexOf("\n")).trimmed();
        buffer.remove(0, buffer.indexOf("\n") + 1); // Remove processed data from the buffer

        qDebug() << "Scanned UID:" << uid;

        // Check if UID is valid and dialog is active
        if (!uid.isEmpty() && waitingDialog) {
            waitingDialog->accept(); // Close the waiting dialog
            waitingDialog = nullptr;

            // Get the selected employee's ID from the table
            QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
            QString employeeID = ui->tableView->model()->index(selectedRows[0].row(), 1).data().toString(); // Adjust the column index for IDEMP

            // Save the UID to the database
            saveTokenToDatabase(uid, employeeID);
        }
    }
}
void MainWindow::saveTokenToDatabase(const QString &uid, const QString &employeeID) {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET TOKEN_LOGIN = :token WHERE IDEMP = :id");
    query.bindValue(":token", uid);
    query.bindValue(":id", employeeID);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Token successfully assigned to employee.");
        qDebug() << "Token UID:" << uid << "assigned to employee ID:" << employeeID;
    } else {
        QMessageBox::critical(this, "Error", "Failed to save token to database: " + query.lastError().text());
        qDebug() << "Database error:" << query.lastError().text();
    }
}

// Function to load employee data from the database
void MainWindow::loadEmployeeData()
{
    QSqlQuery query;
    query.prepare("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE, IMAGE_PATH FROM EMPLOYEE");

    if (!query.exec()) {
        qDebug() << "Error loading data from database: " << query.lastError().text();
        return;
    }

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"CINEMP", "IDEMP", "FULL NAME", "HIRE DATE", "ROLE", "SALARY", "EMAIL", "AGE", "GENDER", "PHONE"});

    imagePaths.clear();  // Clear previous image paths

    while (query.next()) {
        QList<QStandardItem *> rowItems;
        QString cin = query.value("CINEMP").toString();
        QString imagePath = query.value("IMAGE_PATH").toString();

        rowItems << new QStandardItem(cin);
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

        // Add the image path to the map
        imagePaths[cin] = imagePath;

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
        orderByClause = sortColumn + " DESC";  // Most recent hire date first
    } else if (selectedOption == "Role") {
        sortColumn = "ROLE";
        orderByClause = sortColumn + " ASC";  // Alphabetical order
    } else if (selectedOption == "Age") {
        sortColumn = "DATE_OF_BIRTH";  // Sorting by Date of Birth to calculate Age
        orderByClause = sortColumn + " ASC";  // Youngest first (by DOB)
    } else if (selectedOption == "Gender") {
        orderByClause = "CASE WHEN GENDER = 'F' THEN 0 ELSE 1 END, GENDER ASC";  // Female first
    }

    // Query the data with Date of Birth included for sorting but exclude it from the table view
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString query = QString("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE FROM EMPLOYEE ORDER BY %1").arg(orderByClause);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error sorting data: " << model->lastError().text();
        return;
    }

    // Create a new model for the table view excluding the DATE_OF_BIRTH column
    QStandardItemModel *tableModel = new QStandardItemModel(this);
    tableModel->setHorizontalHeaderLabels({"CINEMP", "IDEMP", "FULL NAME", "HIRE DATE", "ROLE", "SALARY", "EMAIL", "AGE", "GENDER", "PHONE"});

    for (int row = 0; row < model->rowCount(); ++row) {
        QList<QStandardItem *> rowItems;

        // Add the fields excluding DATE_OF_BIRTH
        for (int col = 0; col < model->columnCount(); ++col) {
            if (model->headerData(col, Qt::Horizontal).toString() != "DATE_OF_BIRTH") {
                rowItems << new QStandardItem(model->record(row).value(col).toString());
            }
        }

        // Calculate AGE dynamically from DATE_OF_BIRTH and insert it in the appropriate column
        QDate dob = model->record(row).value("DATE_OF_BIRTH").toDate();
        int age = Employee::calculateAge(dob);
        rowItems.insert(7, new QStandardItem(QString::number(age)));  // Add AGE after Email

        tableModel->appendRow(rowItems);
    }

    // Set the final model to the table view
    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();
}
void MainWindow::generatePdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (fileName.isEmpty()) return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up font and styles
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont dataFont("Arial", 12);
    QPen titlePen(Qt::darkGreen);
    QPen dataPen(Qt::black);

    // Determine whether an employee is selected
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        // No selection - Export all employees
        QSqlQuery query("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE FROM EMPLOYEE");
        int yOffset = 100;
        int employeeCount = 1;

        while (query.next()) {
            // Title
            painter.setFont(titleFont);
            painter.setPen(titlePen);
            QString title = QString("Employee %1:").arg(employeeCount++);
            QRect titleRect(0, yOffset, pdfWriter.width(), 50);
            painter.drawText(titleRect, Qt::AlignCenter, title);

            // Employee data
            yOffset += 70;
            painter.setFont(dataFont);
            painter.setPen(dataPen);

            painter.drawText(100, yOffset, "CINEMP: " + query.value("CINEMP").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "IDEMP: " + query.value("IDEMP").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "Full Name: " + query.value("FULL_NAME").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "Hire Date: " + query.value("HIRE_DATE").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "Role: " + query.value("ROLE").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "Salary: " + QString::number(query.value("SALARY").toDouble(), 'f', 2));
            yOffset += 50;
            painter.drawText(100, yOffset, "Email: " + query.value("EMAIL").toString());
            yOffset += 50;

            // Date of Birth
            QDate dob = query.value("DATE_OF_BIRTH").toDate();
            if (dob.isValid()) {
                painter.drawText(100, yOffset, "Date of Birth: " + dob.toString("yyyy-MM-dd"));
                yOffset += 50;
                int age = Employee::calculateAge(dob);
                painter.drawText(100, yOffset, "Age: " + QString::number(age));
            } else {
                painter.drawText(100, yOffset, "Date of Birth: Invalid Date");
                yOffset += 50;
                painter.drawText(100, yOffset, "Age: N/A");
            }
            yOffset += 50;

            painter.drawText(100, yOffset, "Gender: " + query.value("GENDER").toString());
            yOffset += 50;
            painter.drawText(100, yOffset, "Phone: " + query.value("PHONE").toString());
            yOffset += 70; // Space between employees

            // Add page break if the content overflows
            if (yOffset > pdfWriter.height() - 150) {
                pdfWriter.newPage();
                yOffset = 100;
            }
        }
    } else {
        // Selection - Export selected employee
        QModelIndex selectedRow = selectedRows[0];
        int row = selectedRow.row();

        QString cin = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
        QString id = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
        QString name = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
        QString hireDate = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
        QString role = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();
        QString salary = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();
        QString email = ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString();
        int age = ui->tableView->model()->data(ui->tableView->model()->index(row, 7)).toInt();
        QString gender = ui->tableView->model()->data(ui->tableView->model()->index(row, 8)).toString();
        QString phone = ui->tableView->model()->data(ui->tableView->model()->index(row, 9)).toString();

        // Title
        painter.setFont(titleFont);
        painter.setPen(titlePen);
        QRect titleRect(0, 100, pdfWriter.width(), 50);
        painter.drawText(titleRect, Qt::AlignCenter, "Selected Employee");

        // Employee data
        painter.setFont(dataFont);
        painter.setPen(dataPen);
        int yOffset = 200;

        painter.drawText(100, yOffset, "CINEMP: " + cin);
        yOffset += 50;
        painter.drawText(100, yOffset, "IDEMP: " + id);
        yOffset += 50;
        painter.drawText(100, yOffset, "Full Name: " + name);
        yOffset += 50;
        painter.drawText(100, yOffset, "Hire Date: " + hireDate);
        yOffset += 50;
        painter.drawText(100, yOffset, "Role: " + role);
        yOffset += 50;
        painter.drawText(100, yOffset, "Salary: " + salary);
        yOffset += 50;
        painter.drawText(100, yOffset, "Email: " + email);
        yOffset += 50;
        painter.drawText(100, yOffset, "Age: " + QString::number(age));
        yOffset += 50;
        painter.drawText(100, yOffset, "Gender: " + gender);
        yOffset += 50;
        painter.drawText(100, yOffset, "Phone: " + phone);
    }

    // Add the image at the bottom-right corner
    QPixmap pixmap("E:/2A/projetcpp-smart-pharmacy-2a30/Resources/icon.png");

    if (!pixmap.isNull()) {
        // Get the original width and height of the image
        int originalWidth = pixmap.width();
        int originalHeight = pixmap.height();

        // Set the maximum width and height for the image in the PDF
        int maxWidth = 200;
        int maxHeight = 200;

        // Calculate the scaled dimensions while maintaining the aspect ratio
        int scaledWidth = maxWidth;
        int scaledHeight = (originalHeight * maxWidth) / originalWidth;
        if (scaledHeight > maxHeight) {
            scaledHeight = maxHeight;
            scaledWidth = (originalWidth * maxHeight) / originalHeight;
        }

        // Center the image at the bottom-right corner of the page
        int x = pdfWriter.width() - scaledWidth - 50; // 50 px margin from the right
        int y = pdfWriter.height() - scaledHeight - 50; // 50 px margin from the bottom

        // Draw the scaled image
        QRect imageRect(x, y, scaledWidth, scaledHeight);
        painter.drawPixmap(imageRect, pixmap);
    }

    painter.end();
    QMessageBox::information(this, tr("PDF Generated"), tr("The employee data has been saved as a PDF."));
}


void MainWindow::on_statistique_clicked()
{
    // Set the title for the statistics window
    this->setWindowTitle("PHARMEASE - Gender Statistics");

    // Pie series for gender distribution
    QPieSeries *genderSeries = new QPieSeries();

    // Ensure database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open!";
        QMessageBox::critical(this, "Database Error", "Failed to open database connection.");
        return;
    }

    // Query to count males and females
    QSqlQuery query(db);
    query.prepare("SELECT GENDER, COUNT(*) FROM EMPLOYEE GROUP BY GENDER");

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Query Error", "Could not execute query.");
        return;
    }

    // Add data to the pie series
    while (query.next()) {
        QString gender = query.value(0).toString();
        int count = query.value(1).toInt();
        genderSeries->append(gender + " (" + QString::number(count) + ")", count);
    }

    // Customize the pie chart
    genderSeries->setLabelsVisible();
    genderSeries->setLabelsPosition(QPieSlice::LabelOutside);
    for (auto slice : genderSeries->slices()) {
        slice->setLabelColor(Qt::black);
        slice->setBorderColor(Qt::yellow);
        slice->setBorderWidth(2);
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(genderSeries);
    chart->setTitle("Gender Distribution");
    chart->setAnimationOptions(QChart::AllAnimations);

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Display the chart in a new window
    QWidget *statsWindow = new QWidget();
    statsWindow->setWindowTitle("Employee Gender Statistics");
    QVBoxLayout *layout = new QVBoxLayout(statsWindow);
    layout->addWidget(chartView);

    statsWindow->resize(800, 600);
    statsWindow->show();
}
void MainWindow::on_loadButton_clicked()
{
    loadEmployeeData();
}
void MainWindow::on_searchButton_clicked()
{
    // Create a dialog for search
    QDialog searchDialog(this);
    searchDialog.setWindowTitle("Search Employee");
    QVBoxLayout *layout = new QVBoxLayout(&searchDialog);

    // ComboBox for selecting the search criterion
    QLabel *comboLabel = new QLabel("Search By:");
    QComboBox *searchCriteria = new QComboBox();
    searchCriteria->addItems({"Name", "CIN", "Email", "Phone"});
    layout->addWidget(comboLabel);
    layout->addWidget(searchCriteria);

    // LineEdit for search input
    QLabel *lineEditLabel = new QLabel("Enter Value:");
    QLineEdit *searchInput = new QLineEdit();
    layout->addWidget(lineEditLabel);
    layout->addWidget(searchInput);

    // OK and Cancel buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(cancelButton, &QPushButton::clicked, &searchDialog, &QDialog::reject);

    // Connect the OK button to perform the search
    connect(okButton, &QPushButton::clicked, [=, &searchDialog]() {
        QString filterField = searchCriteria->currentText();
        QString searchValue = searchInput->text().trimmed();

        if (searchValue.isEmpty()) {
            QMessageBox::warning(&searchDialog, "Input Error", "Please enter a value to search.");
            return;
        }

        QString sqlField;
        if (filterField == "Name") sqlField = "FULL_NAME";
        else if (filterField == "CIN") sqlField = "CINEMP";
        else if (filterField == "Email") sqlField = "EMAIL";
        else if (filterField == "Phone") sqlField = "PHONE";

        // Prepare the query, matching the same fields as loadEmployeeData
        QSqlQuery query;
        query.prepare(QString("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE "
                              "FROM EMPLOYEE WHERE LOWER(%1) LIKE LOWER(:value)").arg(sqlField));
        query.bindValue(":value", "%" + searchValue + "%");

        if (!query.exec()) {
            qDebug() << "Error executing search query:" << query.lastError().text();
            QMessageBox::critical(&searchDialog, "Query Error", "Failed to execute search query.");
            return;
        }

        // Populate the table view with search results
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels({"CINEMP", "IDEMP", "FULL NAME", "HIRE DATE", "ROLE", "SALARY", "EMAIL", "AGE", "GENDER", "PHONE"});

        while (query.next()) {
            QList<QStandardItem *> rowItems;
            QString cin = query.value("CINEMP").toString();

            rowItems << new QStandardItem(cin);
            rowItems << new QStandardItem(query.value("IDEMP").toString());
            rowItems << new QStandardItem(query.value("FULL_NAME").toString());
            rowItems << new QStandardItem(query.value("HIRE_DATE").toDate().toString("yyyy-MM-dd"));
            rowItems << new QStandardItem(query.value("ROLE").toString());
            rowItems << new QStandardItem(QString::number(query.value("SALARY").toDouble(), 'f', 2));
            rowItems << new QStandardItem(query.value("EMAIL").toString());

            // Calculate AGE dynamically from DATE_OF_BIRTH
            QDate dob = query.value("DATE_OF_BIRTH").toDate();
            int age = Employee::calculateAge(dob);
            rowItems << new QStandardItem(QString::number(age));

            rowItems << new QStandardItem(query.value("GENDER").toString());
            rowItems << new QStandardItem(query.value("PHONE").toString());

            model->appendRow(rowItems);
        }

        // Set the final model to the table view
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();

        searchDialog.accept();
    });

    searchDialog.exec();
}

void MainWindow::setupRoleBasedAccess()
{
    if (userRole == "Pharmacy IT Specialist") {
        // Allow full access and show the "employeepage"
        ui->stackedWidget->setCurrentWidget(ui->employeepage);
    } else {
        // Restrict access and show the "otherpages"
        ui->stackedWidget->setCurrentWidget(ui->otherpages);

        // Optionally disable access to "employeepage" buttons
        ui->employeebutton1->setEnabled(true);
    }
}
void MainWindow::on_logoutButton_clicked()
{
    // Close the current MainWindow
    this->close();

    // Show the Login dialog
    Login loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // If login is successful again, show a new MainWindow
        QString role = loginDialog.getRole();
        MainWindow *mainWindow = new MainWindow(nullptr, role);
        mainWindow->show();
    } else {
        // Exit the application if login is canceled
        qApp->quit();
    }
}


void MainWindow::onTableSelectionChanged()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        ui->imageLabel->clear();
        return;
    }

    QString cin = ui->tableView->model()->index(selectedRows[0].row(), 0).data().toString();  // CINEMP is in column 0
    QString imagePath = imagePaths.value(cin);

    qDebug() << "Selected CINEMP:" << cin;
    qDebug() << "Image path for selected employee:" << imagePath;

    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        QPixmap pixmap(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Error: Unable to load the image from path:" << imagePath;
            ui->imageLabel->clear();
        } else {
            ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        qDebug() << "Error: Invalid or missing image path.";
        ui->imageLabel->clear();
    }
}
void MainWindow::on_ajouter_produit_2_clicked()
{

    int IdPre = ui->lineEdit_Idp_2->text().toInt(); // Assuming lineEdit_Idp is used for ID_PRE
    QString Reference = ui->lineEdit_Reference_2->text();
    QString DrName = ui->lineEdit_DrName_2->text();
    QString Instructions = ui->lineEdit_Instructions_2->text();

    // Create an Ordonnance object
    Ordonnance ord(IdPre, Reference, DrName, Instructions);

    // Call ajouter() method to add Ordonnance to database
    bool test = ord.ajouter();

    // Check result and show message
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        Ajouter_Histo(IdPre);
        ui->tableView_3->setModel(ord.display());
        ui->lineEdit_Idp_2->clear();
        ui->lineEdit_Reference_2->clear();
        ui->lineEdit_DrName_2->clear();
        ui->lineEdit_Instructions_2->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    Ordonnance ord;

    // Récupérer l'index de la ligne actuellement sélectionnée dans la table
    QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();

    // Vérifier si une ligne est bien sélectionnée
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Erreur", "Aucune ligne sélectionnée !");
        return;
    }

    // Extraire l'ID de la ligne sélectionnée (en supposant que l'ID est dans la première colonne, colonne 0)
    int IdPre = ui->tableView_3->model()->data(ui->tableView_3->model()->index(currentIndex.row(), 0)).toInt();

    // Appeler la méthode de suppression avec l'ID récupéré
    bool test = ord.supprimer(IdPre);

    // Vérifier si la suppression a été effectuée avec succès
    if (test) {
        // Mettre à jour la tableView après suppression
        ui->tableView_3->setModel(ord.display());

        // Ajouter à l'historique de suppression
        Supprimer_Histo(IdPre);

        // Message de confirmation
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        // Message d'erreur si la suppression échoue
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

    }
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    // Récupérer l'index de la ligne cliquée
    int row = index.row();

    // Extraire les données de la ligne cliquée
    int IdPre = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();
    QString Reference = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString DrName = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
    QString Instructions = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();

    // Remplir les champs QLineEdit avec les données de la ligne sélectionnée
    ui->lineEdit_Idp_2->setText(QString::number(IdPre));
    ui->lineEdit_Reference_2->setText(Reference);
    ui->lineEdit_DrName_2->setText(DrName);
    ui->lineEdit_Instructions_2->setText(Instructions);

}
void MainWindow::on_Modifier_2_clicked()
{
    // Récupérer les données modifiées des champs QLineEdit
    int IdPre = ui->lineEdit_Idp_2->text().toInt();
    QString Reference = ui->lineEdit_Reference_2->text();
    QString DrName = ui->lineEdit_DrName_2->text();
    QString Instructions = ui->lineEdit_Instructions_2->text();

    // Créer un objet Ordonnance avec les nouvelles données
    Ordonnance ord(IdPre, Reference, DrName, Instructions);

    // Appel à la méthode de mise à jour (modifier)
    bool test = ord.modifier();
    if (test) {
        // Si la modification est réussie, mettre à jour la tableView
        ui->tableView_3->setModel(ord.display());
        Modifier_Histo(IdPre);
        QMessageBox::information(this, "Succès", "Modification réussie.");

        // Réinitialiser les champs de saisie
        ui->lineEdit_Idp_2->clear();
        ui->lineEdit_Reference_2->clear();
        ui->lineEdit_DrName_2->clear();
        ui->lineEdit_Instructions_2->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "La modification a échoué.");
    }
}
void MainWindow::rechercheDynamique() {
    // Récupérer les valeurs actuelles des champs de recherche
    QString id = ui->idLineEdit_2->text();
    QString REFERENCE = ui->ReferenceLineEdit_2->text();

    // Préparer la requête SQL dynamique
    QString queryStr = "SELECT * FROM ORDONNANCE WHERE 1=1"; // '1=1' simplifie l'ajout de conditions

    if (!id.isEmpty()) {
        queryStr += " AND ID_PRE = " + id;
    }

    if (!REFERENCE.isEmpty()) {
        queryStr += " AND REFERENCE LIKE '%" + REFERENCE + "%'";
    }

    // Exécuter la requête et l'afficher dans le QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec()) {
        model->setQuery(query);
        ui->tableView_3->setModel(model);
        ui->tableView_3->resizeColumnsToContents();  // Ajuster la taille des colonnes
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError().text();
    }
}






void MainWindow::on_Trier_2_clicked()
{

    // Créer une requête SQL pour trier les données par la date de création
    QString queryStr = "SELECT ID_PRE, REFERENCE, DR_NAME, INSSTRUCTIONS  FROM ORDONNANCE "
                       "ORDER BY REFERENCE ASC";  // Tri décroissant

    // Créer un modèle de requête
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);

    // Vérifier les erreurs de la requête
    if (model->query().lastError().isValid()) {
        qDebug() << "Error executing query:" << model->query().lastError().text();
    } else {
        // Mettre à jour la vue avec le modèle trié
        ui->tableView->setModel(model);

        // Activer le tri par colonne dans le QTableView
        ui->tableView->setSortingEnabled(true);
    }
}


void MainWindow::on_pushButton_4_clicked()
{

    QPdfWriter pdf("C:/Liste_ordonnance.pdf");

    QPainter painter(&pdf);
    int i = 4100;



    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des ordonnance");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID_PRE");
    painter.drawText(2000,3600,"REFERENCE");
    painter.drawText(3300,3600,"DR_NAME");
    painter.drawText(4500,3600,"INSSTRUCTIONS");
    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from ORDONNANCE");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(3300,i,query.value(2).toString());
        painter.drawText(4500,i,query.value(3).toString());
        painter.drawText(7500,i,query.value(4).toString());

        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr(".\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_sendChatBtn_clicked()
{

    QString text, space = "";
    float rassemblance = 0;
    int tr = 0;
    QString msg = ui->inputChatbot_2->text();
    ui->chatBot_4->appendPlainText(space);
    ui->chatBot_4->appendPlainText(msg);


    QSqlQuery qry, query;

    if (msg[0] != QChar('#')) {
        qry.prepare("SELECT * FROM chatbot");
        if (!qry.exec()) {
            qDebug() << "Error executing query: " ;
            return;
        }

        while (qry.next() && tr == 0) {
            QString quest = qry.value(0).toString();
            int eq = 0, dif = 0;
            for (int i = 0; i < std::min(msg.size(), quest.size()); i++) {
                if (quest[i] == msg[i])
                    eq++;
                else
                    dif++;
            }
            rassemblance = (eq / static_cast<float>(msg.size())) * 100;
            if (rassemblance > 80) {
                if (qry.value(1).toString() == "Details") {
                    QString id = msg.mid(18, msg.length() - 18);


                } else {
                    ui->chatBot_4->appendPlainText("\n" + qry.value(1).toString());
                }
                tr = 1;
            }
        }

        if (tr == 0) {
            ui->chatBot_4->appendPlainText("Voulez-vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
            ui->labelCache_2->setText(msg);
        }
    } else {
        QString msg1 = msg.mid(1);
        if (msg1.isEmpty()) {
            ui->chatBot_4->appendPlainText("Vous n'avez pas entré de réponse valide.");
            return;
        }

        query.prepare("INSERT INTO chatbot (quest, rep) VALUES (:quest, :rep)");
        query.bindValue(":quest", ui->labelCache_2->text());
        query.bindValue(":rep", msg1);
        if (!query.exec()) {

            return;
        }

        ui->chatBot_4->appendPlainText("\nMerci ! Pour cette information");
    }
}
void MainWindow::on_Retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_chatBot_3_clicked()
{
  ui->stackedWidget_2->setCurrentIndex(2);
}



void MainWindow::on_Statistique_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_Statistique_4_clicked()
{
    Ordonnance ord;

    // Supprimer tous les widgets existants dans le layout horizontalLayout_3
    QLayoutItem* item;
    while ((item = ui->horizontalLayout_2->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Obtenez les statistiques par type
    QMap<QString, int> statistics = ord.Statistics();

    // Créez une série de secteurs (camembert) pour afficher les statistiques
    QPieSeries *series = new QPieSeries();

    // Ajoute chaque secteur avec la valeur correspondante
    for (const QString &CATEGORIE : statistics.keys()) {
        QPieSlice *slice = series->append(CATEGORIE, statistics[CATEGORIE]);
        slice->setLabelVisible(true);  // Affiche les étiquettes
        slice->setLabel(QString("%1: %2").arg(CATEGORIE).arg(statistics[CATEGORIE])); // Personnalise l'étiquette
        slice->setBrush(QBrush(QColor::fromHsv(rand() % 360, 255, 255))); // Choisit une couleur aléatoire
    }

    // Crée le graphique circulaire
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques par DR_NAME");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Crée un widget QChartView pour afficher le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique dans le layout horizontalLayout_3
    ui->horizontalLayout_2->addWidget(chartView);

}


void MainWindow::on_RetourS_2_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

// General function to log any history message
void MainWindow::logHistory(const QString &message)
{
    // Open the file for appending
    QFile file("C:/Users/sarra/OneDrive/Bureau/Atelier_Connexion/Atelier_Connexion/ordonnance_history.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << message << "\n";  // Append the log message with a newline
        file.close();  // Close the file after writing
    } else {
        qDebug() << "Failed to open the file for writing.";
    }
}

// Function to log depot addition
void MainWindow::Ajouter_Histo(int Id)
{
    // Get the current date and time
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Create the log message for addition
    QString message = QString("ordonnance avec ID %1 ajouté à %2").arg(Id).arg(currentDate);

    // Write the message to the log file
    logHistory(message);
}

// Function to log depot modification
void MainWindow::Modifier_Histo(int Id)
{
    // Get the current date and time
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Create the log message for modification
    QString message = QString("ordonnance avec ID %1 modifié à %2").arg(Id).arg(currentDate);

    // Write the message to the log file
    logHistory(message);
}

// Function to log depot deletion
void MainWindow::Supprimer_Histo(int Id)
{
    // Get the current date and time
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // Create the log message for deletion
    QString message = QString("ordonnance avec ID %1 supprimé à %2").arg(Id).arg(currentDate);

    // Write the message to the log file
    logHistory(message);
}
void MainWindow::connectToDatabase() {
    // Initialize the database connection
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("2a30source");
    db.setUserName("projetcpp2a30");
    db.setPassword("2a30user");
     // Attempt to open the database connection
    if (!db.open()) {
        // Display an error message box if connection fails
        QMessageBox::critical(this, "Database Connection Error",
                              "Unable to connect to the database: " + db.lastError().text());
        qDebug() << "Database connection error: " << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }
}

void MainWindow::getSupplier(){
    if (!db.isOpen())
        connectToDatabase();
    if (!db.open()) {
        qDebug() << "Error, unable to connect to database";
        qDebug() << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM supplier;")) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return;
    }

    int row = 0;
    ui->listsupplier->clear();
    ui->listsupplier->clearContents();
    ui->listsupplier->setRowCount(0);
    QStringList titles;
    titles << "Cin" << "Id" << "Name" << "Date" << "Contact " << "Adresse" << "Actions";
    ui->listsupplier->setHorizontalHeaderLabels(titles);

    while (query.next()) {
        ui->listsupplier->insertRow(row);
        ui->listsupplier->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // cin
        ui->listsupplier->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // id
        ui->listsupplier->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // name
        ui->listsupplier->setItem(row, 3, new QTableWidgetItem(query.value(3).toDate().toString("yyyy/MM/dd"))); // date
        ui->listsupplier->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // contact
        ui->listsupplier->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // adresse








        QPushButton* updateButton = new QPushButton();
        updateButton->setIcon(QIcon(":/Resources/img/reload.png"));

        QPushButton* deleteButton = new QPushButton();
        deleteButton->setIcon(QIcon(":/Resources/img/delete.png"));
        deleteButton->setStyleSheet("background-color:#ff3333");

        QWidget* cellAction = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(cellAction);
        layout->addWidget(updateButton);
        layout->addWidget(deleteButton);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(5);
        ui->listsupplier->setCellWidget(row, 6, cellAction);

        QObject::connect(deleteButton, &QPushButton::clicked, [=]() {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirm Deletion",
                                          "Are you sure you want to delete this supplier?", QMessageBox::Yes | QMessageBox::No);
            if (reply != QMessageBox::Yes) {
                return;
            }

            connectToDatabase();
            if (!db.open()) {
                qDebug() << "Error, unable to connect to database";
                qDebug() << db.lastError().text();
                return;
            }

            QSqlQuery deleteQuery(db);
            deleteQuery.prepare("DELETE FROM supplier WHERE idsupplier = :id");
            deleteQuery.bindValue(":id", ui->listsupplier->item(row, 1)->text().toInt());

            QMessageBox msb;
            msb.setWindowTitle("Delete Supplier State");
            if (!deleteQuery.exec()) {
                msb.setText("Error deleting supplier: " + deleteQuery.lastError().text());
            } else {
                msb.setText("Supplier has been deleted successfully.");
                getSupplier();
            }
            db.close();
            msb.exec();
        });

        QObject::connect(updateButton, &QPushButton::clicked, [=]() {
            if (!db.isOpen()) {
                connectToDatabase();
            }

            if (!db.open()) {
                qDebug() << "Error: Unable to connect to the database";
                qDebug() << db.lastError().text();
                return;
            }

            QSqlQuery query(db);

            // Get the date from the table and check for validity
            QDate tdate = QDate::fromString(ui->listsupplier->item(row, 3)->text(), "yyyy/MM/dd");
            if (!tdate.isValid()) {
                qDebug() << "Invalid date format";
                return;
            }

            // Use the standard format for most databases (YYYY-MM-DD)
            QString formattedDate = tdate.toString("yyyy/MM/dd");

            // Prepare the query, ensure column names and types are correct
            query.prepare("UPDATE supplier SET cin = :cin, fullname = :name, HIREDATE =to_date(:date,'YYYY/MM/DD'), contact = :contact, adresse = :adresse WHERE idsupplier = :id");

            // Bind values from the table to the query
            query.bindValue(":cin", ui->listsupplier->item(row, 0)->text().toInt());  // Ensure CIN is an integer
            query.bindValue(":id", ui->listsupplier->item(row, 1)->text().toInt());   // Ensure ID is an integer
            query.bindValue(":name", ui->listsupplier->item(row, 2)->text());          // Name is a string
            query.bindValue(":date", formattedDate);                                  // Date in correct format (YYYY-MM-DD)
            query.bindValue(":contact", ui->listsupplier->item(row, 4)->text());      // Contact is a string
            query.bindValue(":adresse", ui->listsupplier->item(row, 5)->text());      // Address is a string

            // Set up the QMessageBox
            QMessageBox msb;
            msb.setWindowTitle("Update Transaction State");

            // Execute the query
            if (!query.exec()) {
                qDebug() << "Error updating supplier: " << query.lastError().text();
                msb.setText("Error updating supplier: " + query.lastError().text());
            } else {
                msb.setText("supplier has been updated successfully.");
                getSupplier();  // Refresh the supplier list
            }

            db.close();
            msb.exec();
       });
        row++;


    }
}

void MainWindow::on_add_supplier_clicked()
{
    if (!db.isOpen())
            connectToDatabase();
        if (!db.open()) {
            qDebug() << "Error, unable to connect to database";
            qDebug() << db.lastError().text();
            return;
        }

        if (ui->cin->text().isEmpty() ||
            ui->id->text().isEmpty() ||
            ui->name->text().isEmpty() ||
            ui->date->text().isEmpty() ||
            ui->contact->text().isEmpty() ||
            ui->adr->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields before adding a supplier.");
            return;
        }

       /* QSqlQuery query(db);
        query.prepare("INSERT INTO supplier (cin, idsupplier, fullname, hiredate, contact, adresse) VALUES (:cin, :id, :name, TO_DATE(:hiredate, 'YYYY-MM-DD'), :contact, :adr)");
        QString formatedDate=QString("to_date(:date,'DD MM YYYY')");

        query.bindValue(":cin", ui->cin->text().toInt());
        query.bindValue(":id", ui->id->text().toInt());
        query.bindValue(":name", ui->name->text());
        query.bindValue(":date", ui->date->text());
        query.bindValue(":contact", ui->contact->text());
        query.bindValue(":adr", ui->adr->text());*/
        QString dateInput = ui->date->text();
            QRegularExpression dateRegex("^\\d{2}/\\d{2}/\\d{4}$"); // format "DD/MM/YYYY"
            if (!dateRegex.match(dateInput).hasMatch()) {
                QMessageBox::warning(this, "Input Error", "Please enter a valid date in the format dd/mm/yyyy.");
                return;
            }

            // Convert to the correct format using QDate
            QDate hireDate = QDate::fromString(dateInput, "dd/MM/yyyy");
            if (!hireDate.isValid()) {
                QMessageBox::warning(this, "Input Error", "The entered date is invalid. Please check the values.");
                return;
            }

            // Prepare the query
            QSqlQuery query(db);

            // Use placeholders, no need to concatenate `formatedDate` into the query string
            query.prepare("INSERT INTO supplier (cin, idsupplier, fullname, hiredate, contact, adresse) "
                          "VALUES (:cin, :id, :name, TO_DATE(:date, 'DD/MM/YYYY'), :contact, :adr)");

            // Bind the values
            query.bindValue(":cin", ui->cin->text().toInt());
            query.bindValue(":id", ui->id->text().toInt());
            query.bindValue(":name", ui->name->text());
            query.bindValue(":date", hireDate.toString("dd/MM/yyyy"));  // Use formatted date as string
            query.bindValue(":contact", ui->contact->text());
            query.bindValue(":adr", ui->adr->text());

        QMessageBox msb;
        msb.setWindowTitle("Add Supplier");

        if (!query.exec()) {
            msb.setText("Error adding supplier: " + query.lastError().text());
        } else {
            msb.setText("Supplier has been added successfully.");
            //ui->date_search->setText("");
            //ui->date_search->setPlaceholderText("Search Date");
            getSupplier();
        }
        msb.exec();
}

void MainWindow::on_SMS_clicked()
{
    QString destinataire = "+21626581955"; // Numéro de téléphone du destinataire
    QString message = ui->smscontenu->toPlainText(); // Récupérer le contenu du champ de texte

    envoyerSMS(destinataire, message);
}


void MainWindow::populateSupplierList()
{
    // Assurez-vous que la connexion à la base de données est ouverte
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "La base de données n'est pas ouverte!";
        return;
    }

    // Préparer la requête SQL pour obtenir le CIN, l'ID et le Nom
    QSqlQuery query;
    query.prepare("SELECT cin, id, nom FROM fournisseurs");  // Requête pour récupérer les trois colonnes

    // Exécuter la requête et vérifier les erreurs
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    // Effacer les anciennes lignes
    ui->listsupplier->clearContents();

    // Compter le nombre de lignes pour configurer la table
    query.last();  // Aller à la dernière ligne
    int rowCount = query.at() + 1;  // Le nombre total de lignes
    ui->listsupplier->setRowCount(rowCount);
    ui->listsupplier->setColumnCount(3);  // Maintenant, 3 colonnes : CIN, ID, et Nom
    ui->listsupplier->setHorizontalHeaderLabels({"CIN", "ID", "Nom"});  // En-têtes modifiés

    // Retourner au début des résultats pour remplir le tableau
    query.first();
    int row = 0;
    do {
        QString cin = query.value(0).toString();  // Récupérer le CIN
        QString id = query.value(1).toString();   // Récupérer l'ID
        QString nom = query.value(2).toString();  // Récupérer le Nom

        ui->listsupplier->setItem(row, 0, new QTableWidgetItem(cin));  // Placer le CIN dans la première colonne
        ui->listsupplier->setItem(row, 1, new QTableWidgetItem(id));   // Placer l'ID dans la deuxième colonne
        ui->listsupplier->setItem(row, 2, new QTableWidgetItem(nom));  // Placer le nom dans la troisième colonne
        row++;
    } while (query.next());
}

void MainWindow::on_qrcodegen_clicked()
{
    // Obtenez la ligne sélectionnée dans listsupplier
    int selectedRow = ui->listsupplier->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a supplier first.");
        return;
    }

    // Récupérer les informations ID, nom et CIN à partir des bonnes colonnes
    QString id = ui->listsupplier->item(selectedRow, 1)->text();   // Colonne 1 : ID (index 1, non 0)
    QString nom = ui->listsupplier->item(selectedRow, 2)->text();  // Colonne 2 : Nom
    QString cin = ui->listsupplier->item(selectedRow, 0)->text();  // Colonne 0 : CIN (index 0, non 3)

    // Vérifier que les informations sont valides
    if (id.isEmpty() || nom.isEmpty() || cin.isEmpty()) {
        QMessageBox::warning(this, "Invalid Data", "Some required information is missing for the selected supplier.");
        return;
    }

    // Créer une chaîne de texte avec l'ID, le nom et le CIN pour le QR code
    QString qrData = QString("ID: %1\nNom: %2\nCIN: %3").arg(id, nom, cin);

    // Générer le QR code
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(qrData.toUtf8().data(), QrCode::Ecc::MEDIUM);
    int sz = qr.getSize();
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    // Remplir l'image du QR code avec les modules (pixels)
    for (int y = 0; y < sz; y++) {
        for (int x = 0; x < sz; x++) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Afficher le QR code dans qrcodeLabel
    ui->qrcodeLabel->setPixmap(QPixmap::fromImage(im.scaled(125, 125, Qt::KeepAspectRatio, Qt::FastTransformation)));
}

void MainWindow::on_sort_clicked()
{
    int dateColumnIndex = 3; // Assuming the date column is at index 3
        qDebug() << "Current dates in column:" << dateColumnIndex;

        // Debug: Print current dates
        for (int row = 0; row < ui->listsupplier->rowCount(); row++) {
            QTableWidgetItem* item = ui->listsupplier->item(row, dateColumnIndex);
            if (item) {
                qDebug() << "Row:" << row << "Date:" << item->text();
            }
        }

        // Collect date and row index pairs for sorting
        QList<QPair<QDate, int>> itemsToSort;
        for (int row = 0; row < ui->listsupplier->rowCount(); row++) {
            QTableWidgetItem* item = ui->listsupplier->item(row, dateColumnIndex);
            if (item) {
                QDate date = QDate::fromString(item->text(), "yyyy/MM/dd"); // Adjust format as needed
                if (date.isValid()) {
                    itemsToSort.append(qMakePair(date, row));
                } else {
                    qDebug() << "Invalid date at row:" << row << "Text:" << item->text();
                }
            }
        }

        // Sort by date in ascending order (change `>` to `<` for descending order)
        std::sort(itemsToSort.begin(), itemsToSort.end(), [](const QPair<QDate, int>& a, const QPair<QDate, int>& b) {
            return a.first > b.first;
        });

        // Collect sorted row items
        QList<QTableWidgetItem*> sortedRowItems;
        for (int i = 0; i < itemsToSort.size(); ++i) {
            int sortedRow = itemsToSort[i].second;
            for (int col = 0; col < ui->listsupplier->columnCount(); ++col) {
                QTableWidgetItem* item = ui->listsupplier->takeItem(sortedRow, col);
                sortedRowItems.append(item);
            }
        }

        // Rearrange table rows
        int rowIndex = 0;
        for (int i = 0; i < itemsToSort.size(); ++i) {
            for (int col = 0; col < ui->listsupplier->columnCount(); ++col) {
                ui->listsupplier->setItem(rowIndex, col, sortedRowItems.takeFirst());
            }
            rowIndex++;
        }

        // Debug: Print sorted dates
        qDebug() << "Dates after sorting:";
        for (int row = 0; row < ui->listsupplier->rowCount(); row++) {
            QTableWidgetItem* item = ui->listsupplier->item(row, dateColumnIndex);
            if (item) {
                qDebug() << "Row:" << row << "Date:" << item->text();
            }
        }
}

void MainWindow::on_exportsup_clicked()
{

    // Open a file dialog to select the save location and filename
      QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (.pdf);;All Files ()"));

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
      painter.drawText(100, 100, "Product List with Quantities Graph");

      int yOffset = 150; // Initial y position for the data and graph
      int i = 1;

      // Create a query to fetch product data
      QSqlQuery query("SELECT cin, idsupplier, fullname, hiredate, contact, adresse FROM supplier ORDER BY hiredate ASC");



      // Prepare the bar chart settings
      int barWidth = 40;       // Width of each bar
      int barSpacing = 20;     // Space between bars
      int chartHeight = 300;   // Height of the chart area

      // Calculate chartWidth and chartXOffset to center the chart on the page
      int chartWidth = (barWidth + barSpacing) * query.size() - barSpacing; // Total width of all bars minus last spacing
      int pageWidth = pdfWriter.width();
      int chartXOffset = (pageWidth - chartWidth) / 2; // Center the chart horizontally
      int chartYOffset = yOffset + 300; // Y position of the chart

      // Iterate over each product and print details in the specified format
      while (query.next()) {
          // Print each product's data in a structured format
          painter.drawText(50, yOffset, "Supplier " + QString::number(i) + ":");
          i++;  // Increment the product count
          yOffset += 60;
          painter.drawText(100, yOffset, "cin: " + query.value("cin").toString());
          yOffset += 60;
          painter.drawText(100, yOffset, "id: " + query.value("idsupplier").toString());
          yOffset += 60;
          painter.drawText(100, yOffset, "name: " + query.value("fullname").toString());
          yOffset += 60;
          painter.drawText(100, yOffset, "date: " + query.value("hiredate").toString());
          yOffset += 60;
          painter.drawText(100, yOffset, "contact: " + query.value("contact").toString());
          yOffset += 60;
          painter.drawText(100, yOffset, "adresse " + query.value("adresse").toString());


          // Draw the bar chart for quantity
          int quantity = query.value("quantite").toInt();
          int barHeight = (quantity * chartHeight) / 100; // Scale based on max quantity (assuming max is 100)

          painter.setBrush(Qt::blue); // Set bar color
          painter.drawRect(chartXOffset + (i - 2) * (barWidth + barSpacing), chartYOffset - barHeight, barWidth, barHeight);

          // Label the bar with product ID
          painter.drawText(chartXOffset + (i - 2) * (barWidth + barSpacing), chartYOffset + 20, query.value("idsupplier").toString());

          // Add some space between products
          yOffset += 100;

          // Check if yOffset goes beyond the page size and create a new page if necessary
          if (yOffset > pdfWriter.height() - 100) {
              pdfWriter.newPage();
              yOffset = 150; // Reset yOffset to start from the top of the new page
              chartYOffset = yOffset + 300; // Reset chart position for the new page
          }
      }

      // Finalize the PDF
      painter.end();

      // Optionally, show a message box to confirm PDF creation
      QMessageBox::information(this, tr("PDF Generated"), tr("The supplier data and graph have been saved as a PDF."));


}
QList<Supplier> *MainWindow::executeQuery(QString request)
{
    QList<Supplier>* lstTransaction= new QList<Supplier>();
    if(!db.isOpen())
    connectToDatabase();
    if(!db.open())
    {
    qDebug()<<"error,unable to connect ro database";
    qDebug()<<db.lastError().text();
    return lstTransaction;
    }


    QSqlQuery query(db);
    qDebug() <<request;
    query.exec(request);


    // QMessageBox msb;
    //msb.setWindowTitle("connection state");
    //msb.setText("connection established "+query.value(1).toString());
    //msb.exec();

    while(query.next()){
    int cin=query.value(0).toInt();
    int id=query.value(1).toInt();//id
    QString name=query.value(2).toString();
    QDate date=query.value(3).toDate();

    QString contact=query.value(4).toString();

    QString adresse=query.value(5).toString();
    lstTransaction->append(Supplier(cin,id,name,date,contact,adresse));
    }

   return lstTransaction;

}
void MainWindow::on_chercher_id_textChanged(const QString &arg1)
{
    QString idValue = ui->chercher_id->text(); // Get ID from the search field
    ui->listsupplier->clearContents();
    ui->listsupplier->setRowCount(0); // Clear existing rows

    // Set column headers
    QStringList titles = { "CIN", "ID", "Name", "Date", "Contact", "Address", "Actions" };
    ui->listsupplier->setHorizontalHeaderLabels(titles);

    // Construct the query based on input
    QString request;
    if (idValue.isEmpty() || !idValue.toInt()) { // Validate input
        request = "SELECT * FROM supplier;";
    } else {
        request = QString("SELECT * FROM supplier WHERE idsupplier = %1;").arg(idValue.toInt());
    }

    // Execute query and get the results
    QList<Supplier>* lstSuppliers = executeQuery(request);

    // Check for null or empty results
    if (!lstSuppliers) {
        qDebug() << "Query execution failed. No data returned.";
        return;
    }
    if (lstSuppliers->isEmpty()) {
        qDebug() << "No suppliers found for the given ID.";
        return;
    }

    // Populate the table with results
    int row = 0;
    for (const auto& supplier : *lstSuppliers) {
        ui->listsupplier->insertRow(row);

        // Populate supplier details in each row
        ui->listsupplier->setItem(row, 0, new QTableWidgetItem(QString::number(supplier.getCin()))); // cin
        ui->listsupplier->setItem(row, 1, new QTableWidgetItem(QString::number(supplier.getId()))); // id
        ui->listsupplier->setItem(row, 2, new QTableWidgetItem(supplier.getName()));               // name
        ui->listsupplier->setItem(row, 3, new QTableWidgetItem(supplier.getDate().toString("yyyy/MM/dd"))); // date
        ui->listsupplier->setItem(row, 4, new QTableWidgetItem(supplier.getContact()));            // contact
        ui->listsupplier->setItem(row, 5, new QTableWidgetItem(supplier.getAdr()));                // address


    // Clean up memory (if applicable)
    //delete lstSuppliers;
            // Add buttons for update and delete actions
            QPushButton* updateButton = new QPushButton();
            updateButton->setIcon(QIcon(":/Resources/img/reload.png"));

            QPushButton* deleteButton = new QPushButton();
            deleteButton->setIcon(QIcon(":/Resources/img/delete.png"));
            deleteButton->setStyleSheet("background-color:#ff3333");

            QWidget* cellAction = new QWidget();
            QHBoxLayout* layout = new QHBoxLayout(cellAction);
            layout->addWidget(updateButton);
            layout->addWidget(deleteButton);
            layout->setContentsMargins(0, 0, 0, 0);
            layout->setSpacing(5);
            ui->listsupplier->setCellWidget(row, 6, cellAction);

            // Fix: Capture the current value of 'row' by value
            int currentRow = row;

            QObject::connect(deleteButton, &QPushButton::clicked, [=]() {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirm Deletion",
                                              "Are you sure you want to delete this supplier?", QMessageBox::Yes | QMessageBox::No);
                if (reply != QMessageBox::Yes) {
                    return;
                }

                connectToDatabase();
                if (!db.open()) {
                    qDebug() << "Error, unable to connect to database";
                    qDebug() << db.lastError().text();
                    return;
                }

                QSqlQuery deleteQuery(db);
                deleteQuery.prepare("DELETE FROM supplier WHERE idsupplier = :id");
                deleteQuery.bindValue(":id", ui->listsupplier->item(currentRow, 1)->text().toInt());

                QMessageBox msb;
                msb.setWindowTitle("Delete Supplier State");
                if (!deleteQuery.exec()) {
                    msb.setText("Error deleting supplier: " + deleteQuery.lastError().text());
                } else {
                    msb.setText("Supplier has been deleted successfully.");
                    getSupplier(); // Refresh the supplier list
                }
                db.close();
                msb.exec();
            });

            QObject::connect(updateButton, &QPushButton::clicked, [=]() {
                if (!db.isOpen()) {
                    connectToDatabase();
                }

                if (!db.open()) {
                    qDebug() << "Error: Unable to connect to the database";
                    qDebug() << db.lastError().text();
                    return;
                }

                QSqlQuery query(db);

                // Get the date from the table and check for validity
                QDate tdate = QDate::fromString(ui->listsupplier->item(row, 3)->text(), "yyyy/MM/dd");
                if (!tdate.isValid()) {
                    qDebug() << "Invalid date format";
                    return;
                }

                // Use the standard format for most databases (YYYY-MM-DD)
                QString formattedDate = tdate.toString("yyyy/MM/dd");

                // Prepare the query, ensure column names and types are correct
                query.prepare("UPDATE supplier SET cin = :cin, fullname = :name, HIREDATE =to_date(:date,'YYYY/MM/DD'), contact = :contact, adresse = :adresse WHERE idsupplier = :id");

                // Bind values from the table to the query
                query.bindValue(":cin", ui->listsupplier->item(row, 0)->text().toInt());  // Ensure CIN is an integer
                query.bindValue(":id", ui->listsupplier->item(row, 1)->text().toInt());   // Ensure ID is an integer
                query.bindValue(":name", ui->listsupplier->item(row, 2)->text());          // Name is a string
                query.bindValue(":date", formattedDate);                                  // Date in correct format (YYYY-MM-DD)
                query.bindValue(":contact", ui->listsupplier->item(row, 4)->text());      // Contact is a string
                query.bindValue(":adresse", ui->listsupplier->item(row, 5)->text());      // Address is a string

                // Set up the QMessageBox
                QMessageBox msb;
                msb.setWindowTitle("Update Transaction State");

                // Execute the query
                if (!query.exec()) {
                    qDebug() << "Error updating supplier: " << query.lastError().text();
                    msb.setText("Error updating transaction: " + query.lastError().text());
                } else {
                    msb.setText("supplier has been updated successfully.");
                    getSupplier();  // Refresh the supplier list
                }

                db.close();
                msb.exec();
           });
            row++;


        }



}
QSqlQueryModel* MainWindow::getventesStats() {
    QSqlQueryModel *model = new QSqlQueryModel;

    // Query to calculate total QUANTITE for each CODEMEDIC
    model->setQuery("SELECT CODEMEDIC, SUM(QUANTITE) as TOTAL_QUANTITE FROM SALES GROUP BY CODEMEDIC;");

    if (model->rowCount() == 0) {
        qDebug() << "No data found for QUANTITE stats!";
    } else {
        qDebug() << "Data found!";
    }

    return model;
}


bool MainWindow::setupVentesStatsChart() {
    QSqlQueryModel* model = getventesStats();

    if (model->rowCount() == 0) {
        qDebug() << "No ventes statistics available!";
        return false;  // Retourne false si aucune donnée n'est disponible
    }

    // Crée une série de barres pour le graphique
    QBarSeries *barSeries = new QBarSeries();

    // Vecteurs pour stocker les QBarSet et les catégories des postes
    QVector<QBarSet*> barSets;
    QVector<QString> categories;

    // Parcourt les données pour créer les ensembles de barres
    for (int row = 0; row < model->rowCount(); ++row) {
        QString code = model->data(model->index(row, 0)).toString();
        int quantite = model->data(model->index(row, 1)).toInt();

        // Crée un QBarSet pour chaque poste
        QBarSet *set = new QBarSet(code);
        *set << quantite;
        barSets.append(set);
        categories.append(code);
    }

    // Ajoute les ensembles de barres à la série
    for (QBarSet *set : barSets) {
        barSeries->append(set);
    }

    // Crée le graphique et configure ses propriétés
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chart->setTitle("Number of medic per code");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("quantite");
    axisY->setRange(0, 100);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    // Ajoute les axes au graphique
    chart->addAxis(axisX, Qt::AlignBottom);  // Ajouter un axe X au graphique
    chart->addAxis(axisY, Qt::AlignLeft);    // Ajouter un axe Y au graphique
    barSeries->attachAxis(axisX);             // Attacher l'axe X à la série
    barSeries->attachAxis(axisY);             // Attacher l'axe Y à la série

    // Crée la vue du graphique et active l'anticrénelage
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoie le contenu existant de l'onglet avant d'ajouter le nouveau graphique
    QLayout *oldLayout = ui->tab_4->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Supprime les widgets
            delete item;  // Supprime les items
        }
        delete oldLayout;
    }

    // Ajoute le nouveau graphique au layout de l'onglet
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->tab_4->setLayout(layout);

    return true;  // Retourne true si le graphique est correctement mis à jour
}

void MainWindow::on_refresh_Clicked() {
    qDebug() << "Refreshing statistics...";
    // Appeler la fonction de mise à jour des statistiques
    bool success = setupVentesStatsChart();

        if (success) {
            QMessageBox::information(this, "Rafraîchissement", "Les statistiques ont été mises à jour avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la mise à jour des statistiques. Veuillez réessayer.");
        }
    }
void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupération des valeurs des champs
    int ID_VENTE = ui->id_vente->text().toInt();
    float PRIX = ui->PRIX->text().toFloat();
    int QUANTITE = ui->quantite->text().toInt();
    float TOTALTHT = ui->total->text().toFloat();
    QString CODEMEDIC = ui->codemedic->text();
    QString DESIGNIATION = ui->designiation->text();
    QDate SDATE = ui->date_2->date();

    // Contrôles de saisie
    if (ID_VENTE<=0 || PRIX<=0 || QUANTITE<1 || TOTALTHT<0 || DESIGNIATION.isEmpty() || CODEMEDIC.isEmpty() || SDATE.isNull()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("Veuillez remplir tous les champs obligatoires ."), QMessageBox::Ok);
        return;
    }

    // Vérification que l'ID est un entier positif
    if (ID_VENTE <= 0) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("L'ID doit être un entier positif."), QMessageBox::Ok);
        return;
    }
    if (PRIX <= 0) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur de saisie"), QObject::tr("PRIX doit être un REEL positif."), QMessageBox::Ok);
        return;
    }

    // Vérification que l'âge est supérieur à 18
    if (QUANTITE < 1) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur d'âge"), QObject::tr("QUANTITE INVALIDE."), QMessageBox::Ok);
        return;
    }


    // Création de l'employé
    Ventes v(ID_VENTE, QUANTITE, PRIX,TOTALTHT, CODEMEDIC, DESIGNIATION, SDATE);

        // Attempt to add the sale
        bool test = v.ajouter();
        if (test) {
            QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("The sale has been added successfully."), QMessageBox::Ok);
            ui->tableView->setModel(v.afficher());  // Refresh the view
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to add the sale. Check the data or the database connection."), QMessageBox::Ok);
        }
    }
void MainWindow::on_pushButton_supprimer_clicked()
{
    int ID_VENTE = ui->lineEdit_ID->text().toInt(); // Assuming lineEdit_ID is where the Sale ID is entered

    // Create a Ventes object and attempt to delete the sale with the specified ID
    Ventes v;
    bool test = v.supprimer(ID_VENTE); // Attempt to delete the sale

    // Check the result of the deletion and display appropriate message
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("The sale has been successfully deleted."), QMessageBox::Ok);
        ui->tableView->setModel(v.afficher());  // Refresh the view
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to delete the sale. Please check the ID or database connection."), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    // Retrieve the sale ID from the lineEdit (assuming the sale ID is entered in a QLineEdit)
    int ID_VENTE = ui->lineEdit_ID->text().toInt();

    if (ID_VENTE <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez entrer un ID de vente valide."));
        return;
    }

    // Create and open the modification dialog for the given sale ID
    Dialogmodifier *dialog = new Dialogmodifier(this, ID_VENTE);
    connect(dialog, &Dialogmodifier::VenteModified, this, &MainWindow::onventeModified);
    dialog->exec();
}

void MainWindow::onventeModified()
{
    // Refresh or update the view after a sale modification
    ui->tableView->setModel(Etmp1.afficher());
    QMessageBox::information(this, tr("Succès"), tr("La vente a été modifiée avec succès."));
}

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    QSqlQueryModel *searchModel = Etmp1.chercher(arg1); // Call the chercher method with user input
    if (searchModel != nullptr) {
        ui->tableView->setModel(searchModel); // Update the table view with search results
    } else {
        // Clear the table if no results are found
        ui->tableView->setModel(nullptr);
    }
}


void MainWindow::on_tri_clicked()
{
    QString critere = ui->comboBoxTri->currentText(); // Get the selected sorting criteria
    QSqlQueryModel *model = Etmp1.trier(critere); // Call the `trier` method of the `Ventes` class

    if (model) {
        ui->tableView->setModel(model); // Update the table view with the sorted model
        QMessageBox::information(this, tr("Tri"), tr("Les résultats ont été triés avec succès."));
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de trier les résultats."));
    }
}

void MainWindow::on_resetButton_clicked() {
    // Create a new query model to retrieve all data without filters or sorting
    QSqlQueryModel *model = new QSqlQueryModel();

    // Query to retrieve all sales records without any sorting or filtering
    QString queryStr = "SELECT * FROM SALES"; // Replace with your actual table name if different
    QSqlQuery query;

    if (query.exec(queryStr)) {
        model->setQuery(std::move(query));  // Use move to avoid copying
        // Update the table view with the unfiltered results
        ui->tableView->setModel(model); // Apply the model to the table view
        QMessageBox::information(this, tr("Réinitialisation"), tr("La vue a été réinitialisée."));
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de réinitialiser la vue."));
        qDebug() << "Erreur de réinitialisation : " << query.lastError();
    }
}


void MainWindow::on_exporterEnPDF_clicked()
{
    // Choose file path to save the PDF
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save as PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (filePath.isEmpty()) {
        return;  // User canceled
    }

    // Create the QPdfWriter object
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);  // Set resolution

    // Set up QPainter to write to the PDF
    QPainter painter(&pdfWriter);
    QFont font("Arial", 12);
    painter.setFont(font);
    painter.setPen(Qt::black);

    // Title
    painter.drawText(100, 100, "Liste des ventes");

    int yOffset = 150;  // Initial Y position for data
    int i = 1;  // Sale count

    // Execute the query to retrieve sales
    QSqlQuery query;
    if (!query.exec("SELECT * FROM SALES")) {
        QMessageBox::warning(this, tr("Query Error"), tr("Failed to execute query. Error: %1").arg(query.lastError().text()));
        return;
    }

    // Iterate over each sale and write details in a structured format
    while (query.next()) {
        // Sale header
        painter.drawText(50, yOffset, "Vente " + QString::number(i) + ":");
        i++;  // Increment count
        yOffset += 70;

        // Print each attribute
        painter.drawText(100, yOffset, "ID Vente: " + query.value("ID_VENTE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Prix: " + query.value("PRIX").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Code Médicament: " + query.value("CODEMEDIC").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Désignation: " + query.value("DESIGNIATION").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Quantité: " + query.value("QUANTITE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Total HT: " + query.value("TOTALHT").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Date: " + query.value("SDATE").toString());

        // Add some space between each sale
        yOffset += 140;
    }

    // Finalize the PDF
    painter.end();

    QMessageBox::information(this, tr("Exportation réussie"), tr("Le fichier PDF a été généré avec succès."));
}
void MainWindow::on_dashboardButton_clicked() {
    DashboardDialog *dashboardDialog = new DashboardDialog(this);
    dashboardDialog->exec();  // Open the dialog modally
    delete dashboardDialog;   // Clean up after closing
}


void MainWindow::on_Historique_clicked()
{
    HistoriqueDialog *dialog = new HistoriqueDialog(this);
    dialog->exec();
}





void MainWindow::on_pushButton_clicked() {
    // Check if text fields are empty
    if (ui->le_id->text().isEmpty() || ui->le_montant->text().isEmpty() ||
        ui->le_status->text().isEmpty() || ui->le_quantite->text().isEmpty() ||
        ui->le_prix->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    // Validate id (must be a positive integer)
    int id = ui->le_id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive ID.");
        return;
    }

    // Validate montant (must be a positive float)
    float montant = ui->le_montant->text().toFloat();
    if (montant <= 0.0f) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive montant.");
        return;
    }

    // Validate quantite (must be a non-negative integer)
    int quantite = ui->le_quantite->text().toInt();
    if (quantite < 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid quantity.");
        return;
    }

    // Validate prix (must be a positive float)
    float prix = ui->le_prix->text().toFloat();
    if (prix <= 0.0f) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive price.");
        return;
    }

    // The date fields are excluded from validation as per the request
    QDate dateComm = ui->le_date->date();
    QDate expirationDate = ui->le_date_expiration->date();

    // Create the Product object and attempt to add it
    Product product(id, dateComm, montant, ui->le_status->text(), quantite, expirationDate, prix);

    if (product.ajouter()) {
        QMessageBox::information(this, "Success", "Addition successful.");
        ui->oui->setModel(product.afficher()); // Refresh the table
    } else {
        QMessageBox::critical(this, "Addition Failed", "Addition not performed.");
    }
}


void MainWindow::on_sup_clicked()
{
    // Get the ID from the line edit for deletion
    int id = ui->le_sup->text().toInt();

    // Assuming 'product' is the Product object responsible for managing products
    bool test = product.supprimer(id); // Call the supprimer function

    if(test)
    {
        ui->oui->setModel(product.afficher()); // Refresh the table view
        QMessageBox::information(this, QObject::tr("Success"),
                    QObject::tr("Suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Error"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_non_clicked()
{
    // Get the ID from the search field
    QString productId = ui->le_search->text();

    // Verify that the ID is not empty
    if (productId.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Veuillez entrer un ID de produit valide dans le champ de recherche.");
        return;
    }

    // Retrieve new values from input fields
    QDate newDate = ui->le_date_2->date();  // Get the date from QDateEdit
    float newMontant = ui->le_montant_2->text().toFloat();
    QString newStatus = ui->le_status_2->text();
    int newQuantite = ui->le_quantite_2->text().toInt();
    QDate newDateExpiration = ui->le_date_expiration_3->date();  // Get expiration date from QDateEdit
    float newPrix = ui->le_prix_2->text().toFloat();

    // Convert the QDate objects to QString in the format 'yyyy-MM-dd' for SQL compatibility
    QString formattedDate = newDate.toString("yyyy-MM-dd");
    QString formattedDateExpiration = newDateExpiration.toString("yyyy-MM-dd");

    //qDebug() << "Formatted Date: " << formattedDate;
    //qDebug() << "Formatted Expiration Date: " << formattedDateExpiration;

    // Prepare the query to update the product in the database
    QSqlQuery query;
    query.prepare("UPDATE product SET DATE_COMM = TO_DATE(:date, 'YYYY-MM-DD'), "
                  "MONTANT_TOTAL = :montant, status = :status, "
                  "QUANTITE = :quantite, DATE_EXPIRATION = TO_DATE(:date_expiration, 'YYYY-MM-DD'), "
                  "PRIX = :prix WHERE id_pro = :id");

    // Bind the values to the query
    query.bindValue(":date", formattedDate);
    query.bindValue(":montant", newMontant);
    query.bindValue(":status", newStatus);
    query.bindValue(":quantite", newQuantite);
    query.bindValue(":date_expiration", formattedDateExpiration);
    query.bindValue(":prix", newPrix);
    query.bindValue(":id", productId);

    // Execute the query
    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Modification", "Le produit a été modifié avec succès.");
            ui->oui->setModel(product.afficher()); // Refresh the table view
        } else {
            QMessageBox::information(this, "Modification", "Aucun produit trouvé avec cet ID. Vérifiez l'ID.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification dans la base de données : " + query.lastError().text());
    }
}


void MainWindow::on_search_clicked()
{
    // Retrieve the ID from the search field
    QString searchTerm = ui->le_search->text();

    // Check if the field is empty
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID.");
        return;
    }

    // Prepare SQL query to search for the product
    QSqlQuery query;
    query.prepare("SELECT DATE_COMM, MONTANT_TOTAL, STATUS, QUANTITE, DATE_EXPIRATION, PRIX FROM product WHERE id_pro = :id");
    query.bindValue(":id", searchTerm);

    if (query.exec()) {
        if (query.next()) {
            // If the product is found, populate the fields
            ui->le_date_2->setDate(query.value(0).toDate());
            ui->le_montant_2->setText(query.value(1).toString());
            ui->le_status_2->setText(query.value(2).toString());
            ui->le_quantite_2->setText(query.value(3).toString());
            ui->le_date_expiration_3->setDate(query.value(4).toDate());
            ui->le_prix_2->setText(query.value(5).toString());

        } else {
            QMessageBox::information(this, "Recherche", "Aucun produit trouvé avec cet ID.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la recherche dans la base de données : " + query.lastError().text());
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->oui->setModel(product.afficher()); // Refresh the table view
}
void MainWindow::on_generatePdfButton_clicked()
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
    painter.drawText(100, 100, "Product List with Quantities Graph");

    int yOffset = 150; // Initial y position for the data and graph
    int i = 1;

    // Create a query to fetch product data
    QSqlQuery query("SELECT id_pro, date_comm, montant_total, status, quantite, date_expiration, prix FROM product ORDER BY quantite ASC");



    // Prepare the bar chart settings
    int barWidth = 40;       // Width of each bar
    int barSpacing = 20;     // Space between bars
    int chartHeight = 300;   // Height of the chart area

    // Calculate chartWidth and chartXOffset to center the chart on the page
    int chartWidth = (barWidth + barSpacing) * query.size() - barSpacing; // Total width of all bars minus last spacing
    int pageWidth = pdfWriter.width();
    int chartXOffset = (pageWidth - chartWidth) / 2; // Center the chart horizontally
    int chartYOffset = yOffset + 300; // Y position of the chart

    // Iterate over each product and print details in the specified format
    while (query.next()) {
        // Print each product's data in a structured format
        painter.drawText(50, yOffset, "Product " + QString::number(i) + ":");
        i++;  // Increment the product count
        yOffset += 60;
        painter.drawText(100, yOffset, "ID: " + query.value("id_pro").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Date: " + query.value("date_comm").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Amount: " + query.value("montant_total").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Status: " + query.value("status").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Quantity: " + query.value("quantite").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Expiration Date: " + query.value("date_expiration").toString());
        yOffset += 60;
        painter.drawText(100, yOffset, "Price: " + query.value("prix").toString());

        // Draw the bar chart for quantity
        int quantity = query.value("quantite").toInt();
        int barHeight = (quantity * chartHeight) / 100; // Scale based on max quantity (assuming max is 100)

        painter.setBrush(Qt::blue); // Set bar color
        painter.drawRect(chartXOffset + (i - 2) * (barWidth + barSpacing), chartYOffset - barHeight, barWidth, barHeight);

        // Label the bar with product ID
        painter.drawText(chartXOffset + (i - 2) * (barWidth + barSpacing), chartYOffset + 20, query.value("id_pro").toString());

        // Add some space between products
        yOffset += 100;

        // Check if yOffset goes beyond the page size and create a new page if necessary
        if (yOffset > pdfWriter.height() - 100) {
            pdfWriter.newPage();
            yOffset = 150; // Reset yOffset to start from the top of the new page
            chartYOffset = yOffset + 300; // Reset chart position for the new page
        }
    }

    // Finalize the PDF
    painter.end();

    // Optionally, show a message box to confirm PDF creation
    QMessageBox::information(this, tr("PDF Generated"), tr("The product data and graph have been saved as a PDF."));
}







void MainWindow::checkProfitNotification(float profit) {
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(this, "Error", "System tray not available!");
        return;
    }

    static QSystemTrayIcon trayIcon(this);

    // Path to the icon (absolute path)
    QString iconPath = "C:/Users/MSI/Downloads/aziz-s-repo-main/aziz-s-repo-main/profit.png";

    // Check if the icon file exists
    if (!QFile::exists(iconPath)) {
        QMessageBox::critical(this, "Error", "Icon file not found at the given path!");
        return;
    }

    // Set the icon if it's not visible
    if (!trayIcon.isVisible()) {
        trayIcon.setIcon(QIcon(iconPath));  // Use the icon from the specified path
        trayIcon.setVisible(true);  // Make sure the icon is visible in the system tray
    }

    // Debugging the values of profit and currentProfit
    //qDebug() << "Profit: " << profit;
    //qDebug() << "Current Profit: " << currentProfit;

    // Check if profit exceeds 1000 and if it has increased by 1000
    if (profit > 1000 && (static_cast<int>(profit) / 1000 > static_cast<int>(currentProfit) / 1000)) {
        // Show message with the total profit
        trayIcon.showMessage("Profit Alert",
                             "Your profit has exceeded " + QString::number(static_cast<int>(profit / 1000) * 1000) + "!\n"
                             "Total Profit: " + QString::number(profit, 'f', 2) + " $",
                             QSystemTrayIcon::Information, 5000);
    }

    currentProfit = profit;  // Update the current profit
}

void MainWindow::on_noti_clicked()
{
    float totalRevenue = 0;

    // Calculate total revenue (quantite * prix)
    QSqlQuery query("SELECT quantite, prix FROM product");
    while (query.next()) {
        int quantity = query.value("quantite").toInt();
        float price = query.value("prix").toFloat();
        totalRevenue += quantity * price;
    }

    //qDebug() << "Total Revenue: " << totalRevenue;  // Debugging the total revenue

    // Trigger notification if totalRevenue exceeds 1000
    checkProfitNotification(totalRevenue);
}


void MainWindow::on_comboBox_activated(int index)
{
    QSqlQuery query("SELECT id_pro, date_comm, montant_total, status, quantite, date_expiration, prix FROM product ORDER BY quantite ASC");
}
void MainWindow::on_calendarWidget_clicked(const QDate &date) {
    // Convertir la date sélectionnée au format "YYYY-MM-DD"
    QString selectedDate = date.toString("yyyy-MM-dd");

    // Préparer la requête SQL pour les produits expirant à la date sélectionnée
    QSqlQuery query;
    query.prepare("SELECT id_pro, quantite FROM product WHERE date_expiration = TO_DATE(:selectedDate, 'YYYY-MM-DD')");
    query.bindValue(":selectedDate", selectedDate);

    if (query.exec()) {
        QString lcdMessage;

        if (query.next()) {
            // Construire et envoyer un message pour chaque produit trouvé
            do {
                lcdMessage = "ID: " + query.value("id_pro").toString() + " QT: " + query.value("quantite").toString();
                QByteArray data = lcdMessage.toUtf8();
                if (A.write_to_arduino(data) != 0) {
                    qDebug() << "Failed to write to Arduino!";
                } else {
                    qDebug() << "Message sent to Arduino:" << lcdMessage;
                }
            } while (query.next());
        } else {
            // Si aucun produit n'expire ce jour, vérifier les produits achetés ce jour-là
            query.prepare("SELECT id_pro, quantite FROM product WHERE date_comm = TO_DATE(:selectedDate, 'YYYY-MM-DD')");
            query.bindValue(":selectedDate", selectedDate);

            if (query.exec() && query.next()) {
                do {
                    lcdMessage = "ID: " + query.value("id_pro").toString() + " QT: " + query.value("quantite").toString();
                    QByteArray data = lcdMessage.toUtf8();

                    if (A.write_to_arduino(data) != 0) {
                        qDebug() << "Failed to write to Arduino!";
                    } else {
                        qDebug() << "Message sent to Arduino:" << lcdMessage;
                    }
                } while (query.next());
            } else {
                // Aucun produit trouvé pour cette date
                lcdMessage = "No prod in this date";
                QByteArray data = lcdMessage.toUtf8();

                if (A.write_to_arduino(data) != 0) {
                    qDebug() << "Failed to write to Arduino!";
                } else {
                    qDebug() << "Message sent to Arduino:" << lcdMessage;
                }
            }
        }
    } else {
        // En cas d'échec de la requête SQL
        QString lcdMessage = "DB error!";
        QByteArray data = lcdMessage.toUtf8();
        if (A.write_to_arduino(data) != 0) {
            qDebug() << "Failed to write to Arduino!";
        } else {
            qDebug() << "Message sent to Arduino:" << lcdMessage;
        }
    }


}
void MainWindow::update_champ_de_recherche_aruino()
{
    QByteArray data = A.read_from_arduino();
    QString text = QString::fromUtf8(data).trimmed(); // Remove extra spaces and newlines
    qDebug() << "Sanitized data from Arduino:" << text;

    if (!text.isEmpty()) {
        ui->le_search->insert(text);
    }
}

