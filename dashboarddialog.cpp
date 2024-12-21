#include "dashboarddialog.h"
#include "ui_dashboarddialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include<qmessagebox>

DashboardDialog::DashboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardDialog) {
    ui->setupUi(this);

    // Set default date range to the current month
    QDate currentDate = QDate::currentDate();
    ui->dateEditStart->setDate(currentDate.addMonths(-1));  // Default to 1 month before
    ui->dateEditEnd->setDate(currentDate);                 // Default to today

    // Load data initially
    loadDashboardData();

    // Connect the Load button to refresh the dashboard data
    connect(ui->buttonLoad, &QPushButton::clicked, this, &DashboardDialog::loadDashboardData);

    // Connect close button
    connect(ui->buttonClose, &QPushButton::clicked, this, &DashboardDialog::close);
}

DashboardDialog::~DashboardDialog() {
    delete ui;
}


void DashboardDialog::loadDashboardData() {
        QDate startDate = ui->dateEditStart->date();
        QDate endDate = ui->dateEditEnd->date();

        QSqlQuery query;

        query.prepare("SELECT SUM(TOTALHT) AS totalSpent, "
                      "MAX(CODEMEDIC) AS mostSoldMedic, "
                      "SUM(QUANTITE) AS totalQuantity "
                      "FROM SALES WHERE SDATE BETWEEN :startDate AND :endDate");
        query.bindValue(":startDate", startDate);
        query.bindValue(":endDate", endDate);

        if (query.exec() && query.next()) {
            double totalSpent = query.value("totalSpent").toDouble();
            QString mostSoldMedic = query.value("mostSoldMedic").toString();
            int totalQuantity = query.value("totalQuantity").toInt();

            ui->labelTotalSales->setText(QString::number(totalSpent, 'f', 2) + " DT");
            ui->labelMostSoldProduct->setText(mostSoldMedic);
            ui->labelTotalQuantity->setText(QString::number(totalQuantity));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load data: %1").arg(query.lastError().text()));
        }
    }


    // Update the UI with retrieved data


void DashboardDialog::on_buttonLoad_clicked()
{

        loadDashboardData();
}

