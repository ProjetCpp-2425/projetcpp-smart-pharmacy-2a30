#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QIcon>
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"
#include "connection.h"
#include "login.h"  // Include the Login dialog

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set the application icon globally before showing any windows
    a.setWindowIcon(QIcon("E:/2A/projetcpp-smart-pharmacy-2a30/Resources/icon.png"));

    // Ensure QODBC driver is loaded
    if (!QSqlDatabase::isDriverAvailable("QODBC")) {
        qDebug() << "Error: QODBC driver not available!";
        return -1;
    }

    Connection c;
    if (c.createconnect()) {
        Login loginDialog;  // Show the login dialog first
        if (loginDialog.exec() == QDialog::Accepted) {  // Check if login was successful
            QString role = loginDialog.getRole();  // Fetch the role from the Login dialog
            qDebug() << "Role passed to MainWindow:" << role;

            MainWindow w(nullptr, role);  // Pass the role to MainWindow
            w.show();
            return a.exec();
        } else {
            qDebug() << "Login failed or canceled.";
            return 0;  // Exit if login is canceled or fails
        }
    } else {
        qDebug() << "Database connection failed.";
        return -1;
    }
}
