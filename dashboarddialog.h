#ifndef DASHBOARDDIALOG_H
#define DASHBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class DashboardDialog;
}

class DashboardDialog : public QDialog {
    Q_OBJECT

public:
    explicit DashboardDialog(QWidget *parent = nullptr);
    ~DashboardDialog();

private slots:
    void loadDashboardData();  // Load dashboard data based on the date range

    void on_buttonLoad_clicked();

private:
    Ui::DashboardDialog *ui;
};

#endif // DASHBOARDDIALOG_H
