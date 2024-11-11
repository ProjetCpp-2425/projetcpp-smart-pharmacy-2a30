#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <QProcess>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_oklogin_clicked();
    void on_gotoregister_clicked();
    void on_okregister_clicked();
    void on_showpassword_toggled(bool checked);
    void on_cancel_clicked();
    void on_forget_clicked();
    void on_cancelForget_clicked();

    void sendVerificationCode(const QString &phone);
    void verifyCodeAndEnablePasswordReset();
    void resetPassword();
    void exitApplication();

private:
    Ui::Login *ui;

    QString verificationCode;  // Add this member variable to store the code
    QString hashPassword(const QString &password);
    bool authenticateUser(const QString &cin, const QString &password);
    bool isCinExists(const QString &cin);
    bool isPasswordSet(const QString &cin);
};

#endif // LOGIN_H
