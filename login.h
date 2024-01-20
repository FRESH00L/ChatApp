#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

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

private:
    Ui::Login *ui;
    QString m_usernameLogin;
    QString m_passwordLogin;

};

#endif // LOGIN_H
