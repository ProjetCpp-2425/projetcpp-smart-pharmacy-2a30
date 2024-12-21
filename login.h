#ifndef LOGIN_H
#define LOGIN_H

#include "qserialport.h"
#include <QDialog>
#include <QString>
#include <QSqlQuery>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString getRole() const { return userRole; }

private slots:
    // Login and registration functions
    void on_oklogin_clicked();
    void on_okregister_clicked();
    void on_gotoregister_clicked();
    void on_arduinoLogin_clicked();
    // Forget password flow
    void on_forget_clicked();
    void on_okEmail_clicked();              // Send verification code via email
    void on_okVerificationCode_clicked();  // Verify entered code
    void on_okNewPassword_clicked();       // Set the new password

    // Cancel and navigation functions
    void on_cancelForget_clicked();  // Cancel forget password and go back to login
    void on_cancel_clicked();        // Cancel registration and go back to login
    void exitApplication();          // Exit the application

    // Show/Hide password toggling
    void on_showpassword_toggled(bool checked);
private:
    Ui::Login *ui;
    void startVerificationTimer();
    QString verificationCode;  // Holds the generated verification code
    QString hashPassword(const QString &password);  // Hash the password
    bool authenticateUser(const QString &cin, const QString &password);  // Validate login credentials
    bool isCinExists(const QString &cin);           // Check if CIN exists in the database
    bool isPasswordSet(const QString &cin);         // Check if the user already has a password

    QString buffer;
    QSerialPort *serialPort;
    QString userRole;

};

#endif // LOGIN_H
