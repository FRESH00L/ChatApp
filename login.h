#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "chat.h"
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void userLoggedIn(const QString& username);

private slots:
    void on_signInPushButton_clicked();
    void on_signUpPushButton_clicked();
    void on_showPasswordCheckBox_toggled(bool checked);
    void on_passwordLoginLineEdit_textChanged();
    void on_passwordRegisterLineEdit_textChanged();
    void on_checkPasswordLineEdit_textChanged();

private:
    Ui::Login *ui;
    QString m_usernameLogin;
    QString hashPassword(const QString& password);
    bool checkIfValid(QString _username, QString _password);
    Chat chatWindow;
};

#endif // LOGIN_H
