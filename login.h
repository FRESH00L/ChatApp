#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "chat.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_signInPushButton_clicked();

    void on_signUpPushButton_clicked();

    void on_showPasswordCheckBox_toggled(bool checked);

    void on_passwordLoginLineEdit_textChanged(const QString &Arg1);

    void on_passwordRegisterLineEdit_textChanged(const QString &Arg1);

    void on_checkPasswordLineEdit_textChanged(const QString &Arg1);

    bool checkIfValid(QString,QString);

private:
    Ui::Login *ui;
    QString m_usernameLogin;
    QString hashPassword(const QString& password);
    Chat chatWindow;
};

#endif // LOGIN_H
