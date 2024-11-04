#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
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
        ui->listsupplier->setItem(row, 3, new QTableWidgetItem(query.value(3).toDate().toString("yyyy-MM-dd"))); // date
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
            deleteQuery.prepare("DELETE FROM supplier WHERE id = :id");
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
            if (!db.isOpen())
                connectToDatabase();

            if (!db.open()) {
                qDebug() << "Error, unable to connect to database";
                qDebug() << db.lastError().text();
                return;
            }

            QSqlQuery updateQuery(db);
            QDate tdate = QDate::fromString(ui->listsupplier->item(row, 3)->text(), "yyyy-MM-dd");
            if (!tdate.isValid()) {
                qDebug() << "Invalid date format";
                return;
            }
            QString formattedDate = tdate.toString("yyyy-MM-dd");

            updateQuery.prepare("insert into transactions values (:cin,:idsupplier,:fullname,"+formattedDate+",:contact,:adresse)");
            updateQuery.bindValue(":cin", ui->listsupplier->item(row, 0)->text().toInt());
            updateQuery.bindValue(":id", ui->listsupplier->item(row, 1)->text().toInt());
            updateQuery.bindValue(":date", formattedDate);
            updateQuery.bindValue(":name", ui->listsupplier->item(row, 2)->text());
            updateQuery.bindValue(":contact", ui->listsupplier->item(row, 4)->text());
            updateQuery.bindValue(":adresse", ui->listsupplier->item(row, 5)->text());

            QMessageBox msb;
            msb.setWindowTitle("Update Supplier State");

            if (!updateQuery.exec()) {
                msb.setText("Error updating supplier: " + updateQuery.lastError().text());
            } else {
                msb.setText("Supplier has been updated successfully.");
                getSupplier();
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

    QSqlQuery query(db);
    query.prepare("INSERT INTO supplier (cin, idsupplier, fullname, hiredate, contact, adresse) VALUES (:cin, :id, :name, TO_DATE(:hiredate, 'YYYY-MM-DD'), :contact, :adr)");


    query.bindValue(":cin", ui->cin->text().toInt());
    query.bindValue(":id", ui->id->text().toInt());
    query.bindValue(":name", ui->name->text());
    query.bindValue(":date", ui->date->text());
    query.bindValue(":contact", ui->contact->text());
    query.bindValue(":adr", ui->adr->text());

    QMessageBox msb;
    msb.setWindowTitle("Add Supplier");

    if (!query.exec()) {
        msb.setText("Error adding supplier: " + query.lastError().text());
    } else {
        msb.setText("Supplier has been added successfully.");
        ui->date_search->setText("");
        ui->date_search->setPlaceholderText("Search Date");
        getSupplier();
    }
    msb.exec();
}
