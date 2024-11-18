#include "mainwindow.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qscatterseries.h"
#include "ui_mainwindow.h"
#include "addemployee.h"
#include "editemployee.h"
#include "employee.h"  // Include Employee for the calculateAge function
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
#include <QVBoxLayout>
#include <QVBoxLayout>

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
    connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statistique_clicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);


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
    painter.setFont(QFont("Arial", 12));
    painter.drawText(100, 100, "Employee Data");

    int yOffset = 150;
    QSqlQuery query("SELECT CINEMP, IDEMP, FULL_NAME, HIRE_DATE, ROLE, SALARY, EMAIL, DATE_OF_BIRTH, GENDER, PHONE FROM EMPLOYEE");
    int i = 1;

    while (query.next()) {
        QDate dob = query.value("DATE_OF_BIRTH").toDate();
        int age = Employee::calculateAge(dob);

        painter.drawText(50, yOffset, QString("Employee %1:").arg(i++));
        yOffset += 70;
        painter.drawText(100, yOffset, "CINEMP: " + query.value("CINEMP").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "IDEMP: " + query.value("IDEMP").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Full Name: " + query.value("FULL_NAME").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Hire Date: " + query.value("HIRE_DATE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Role: " + query.value("ROLE").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Salary: " + query.value("SALARY").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Email: " + query.value("EMAIL").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Date of Birth: " + dob.toString("yyyy-MM-dd"));
        yOffset += 70;
        painter.drawText(100, yOffset, "Age: " + QString::number(age));
        yOffset += 70;
        painter.drawText(100, yOffset, "Gender: " + query.value("GENDER").toString());
        yOffset += 70;
        painter.drawText(100, yOffset, "Phone: " + query.value("PHONE").toString());

        yOffset += 110;  // Add space between employees
    }

    painter.end();
    QMessageBox::information(this, tr("PDF Generated"), tr("The employee data has been saved as a PDF."));
}
void MainWindow::on_statistique_clicked()
{
    this->setWindowTitle("PHARMEASE - Employee Statistics");

    // Bar series for salary
    QBarSeries *salarySeries = new QBarSeries();
    QBarSet *salarySet = new QBarSet("Salary");

    QStringList employeeLabels;

    // Ensure database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open!";
        QMessageBox::critical(this, "Database Error", "Failed to open database connection.");
        return;
    }

    // Query to get employee data
    QSqlQuery query(db);
    query.prepare("SELECT FULL_NAME, DATE_OF_BIRTH, SALARY FROM EMPLOYEE");

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        QMessageBox::critical(this, "Query Error", "Could not execute query.");
        return;
    }

    while (query.next()) {
        QString name = query.value("FULL_NAME").toString();
        QDate dateOfBirth = query.value("DATE_OF_BIRTH").toDate();
        double salary = query.value("SALARY").toDouble();

        if (!dateOfBirth.isValid()) {
            qDebug() << "Invalid date of birth for employee:" << name;
            continue;
        }

        // Use Employee::calculateAge to determine age
        Employee tempEmployee;
        tempEmployee.setDateOfBirth(dateOfBirth);
        int age = tempEmployee.calculateAge();

        *salarySet << salary;

        // Format the label: Name, Age, Salary on separate lines
        employeeLabels << QString("%1\n%2\n$%3")
                            .arg(name)
                            .arg(age)
                            .arg(QString::number(salary, 'f', 2));
    }

    salarySeries->append(salarySet);

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(salarySeries);
    chart->setTitle("Employee Statistics: Salary Distribution by Employee");
    chart->setAnimationOptions(QChart::AllAnimations);

    // Configure X-axis for employee labels
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(employeeLabels);
    chart->addAxis(axisX, Qt::AlignBottom);
    salarySeries->attachAxis(axisX);

    // Configure Y-axis for salary values
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Salary ($)");
    chart->addAxis(axisY, Qt::AlignLeft);
    salarySeries->attachAxis(axisY);

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Display the chart in a new window
    QWidget *statsWindow = new QWidget();
    statsWindow->setWindowTitle("Employee Statistics");
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
    searchCriteria->setStyleSheet(R"(
        QComboBox {
            background-color: #3d3d3d;
            color: #ffffff;
            font-size: 14px;
            font-weight: bold;
            border-radius: 7px;
            border: 2px solid #00ff00;
            padding: 8px 15px;
            outline: none;
        }

        QComboBox::drop-down {
            border: none;
            background: transparent;
        }

        QComboBox QAbstractItemView {
            background-color: #3d3d3d;
            color: #ffffff;
            border: 2px solid #00ff00;
            selection-background-color: #2d89ef;
            selection-color: #ffffff;
            border-radius: 7px;
        }

        QComboBox:hover {
            color: #e0e0e0;
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));
            border-color: #2d89ef;
        }

        QComboBox:pressed, QComboBox:on {
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:1 rgba(45, 45, 45, 255));
            border-color: #da532c;
        }
    )");
    layout->addWidget(comboLabel);
    layout->addWidget(searchCriteria);

    // LineEdit for search input with stylesheet
    QLabel *lineEditLabel = new QLabel("Enter Value:");
    QLineEdit *searchInput = new QLineEdit();
    searchInput->setStyleSheet(R"(
        QLineEdit {
            border-style: solid;
            background-color: #3d3d3d;
            color: #fff;
            border-radius: 7px;
            border-width: 2px;
            border-color: #00ff00;
            padding: 6px;
            outline: none;
        }

        QLineEdit:hover {
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));
            border-color: #2d89ef;
        }

        QLineEdit:focus {
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:1 rgba(45, 45, 45, 255));
            border-color: #da532c;
        }
    )");
    layout->addWidget(lineEditLabel);
    layout->addWidget(searchInput);

    // OK and Cancel buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");
    okButton->setStyleSheet(R"(
        QPushButton {
            border-style: solid;
            background-color: #3d3d3d;
            color: #ffffff;
            font-size: 11px;
            font-weight: bold;
            border-radius: 7px;
            border-width: 2px;
            border-color: #00ff00;
            padding: 8px 15px;
            outline: none;
        }

        QPushButton:hover {
            color: #e0e0e0;
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));
            border-color: #2d89ef;
        }

        QPushButton:pressed {
            background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:1 rgba(45, 45, 45, 255));
            border-color: #da532c;
        }
    )");

    cancelButton->setStyleSheet(okButton->styleSheet());  // Use same style for cancel button
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(cancelButton, &QPushButton::clicked, &searchDialog, &QDialog::reject);

    // Update validation based on combo box selection
    connect(searchCriteria, &QComboBox::currentTextChanged, [=](const QString &text) {
        if (text == "CIN" || text == "Phone") {
            // Validator for 8-digit numeric values
            searchInput->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d{8}"), searchInput));
        } else if (text == "Email") {
            // Validator for email format
            QRegularExpression emailRegEx(R"([\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,})");
            searchInput->setValidator(new QRegularExpressionValidator(emailRegEx, searchInput));
        } else {
            // No validator for Name, allowing any text
            searchInput->setValidator(nullptr);
        }
    });

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

        QSqlQuery query;
        query.prepare(QString("SELECT * FROM EMPLOYEE WHERE %1 LIKE :value").arg(sqlField));
        query.bindValue(":value", "%" + searchValue + "%");

        if (!query.exec()) {
            qDebug() << "Error executing search query:" << query.lastError().text();
            QMessageBox::critical(&searchDialog, "Query Error", "Failed to execute search query.");
            return;
        }

        // Populate table view with search results
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setHorizontalHeaderLabels({"CINEMP", "IDEMP", "FULL NAME", "HIRE DATE", "ROLE", "SALARY", "EMAIL", "AGE", "GENDER", "PHONE"});

        while (query.next()) {
            QList<QStandardItem *> rowItems;
            for (int i = 0; i < query.record().count(); i++) {
                rowItems << new QStandardItem(query.value(i).toString());
            }
            model->appendRow(rowItems);
        }

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        searchDialog.accept();
    });

    searchDialog.exec();
}
