#include "mainwindow.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qscatterseries.h"
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
// Constructor
MainWindow::MainWindow(QWidget *parent, const QString &role) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    userRole(role)
{
    ui->setupUi(this);
    this->setWindowTitle("PHARMEASE - Dashboard");
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
        ui->employeebutton1->setEnabled(false);
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

