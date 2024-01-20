#include "login.h"
#include "ui_login.h"
#include "database.h"
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


void Login::on_signInPushButton_clicked()
{
    qDebug() << "info - Funkcja signIn - Open";
    m_usernameLogin = ui->usernameLoginLineEdit->text();
    m_passwordLogin = ui->passwordLoginLineEdit->text();

    DataBase db;
    if(db.openconnection())
    {
        qDebug() << "info - if: db.openconnection - OK";
        if(db.checkLogin(m_usernameLogin, m_passwordLogin))
        {
            qDebug() << "info - proper user - OK";
            QMessageBox::information(this, "Login", "Zalogowano pomyślnie.");
            QSqlQuery query("SELECT * FROM users");

            if (query.exec()) {
                while (query.next()) {
                    QString username = query.value("username").toString();
                    QString password = query.value("password").toString();
                    qDebug() << "Użytkownik:" << username << ", Hasło:" << password;
                }
            } else {
                qDebug() << "! -- Błąd zapytania SQL:" << query.lastError().text();
            }
            chatWindow.show();
            close();
        }
        else
            QMessageBox::warning(this,"Login","Błąd logowania.");
        db.closeconnection();
    }
    else
        QMessageBox::critical(this,"Login","Błąd połączenia z bazą");

}



void Login::on_signUpPushButton_clicked()
{
    qDebug() << "info - signUp - Open";

    m_usernameLogin = ui->usernameRegistepLineEdit->text();
    m_passwordLogin = ui->passwordLoginLineEdit->text();

    DataBase db;
    if(db.openconnection())
    {
        qDebug() << "info - if: db.openconnection - OK";
        if(ui->passwordRegisterLineEdit->text() == ui->checkPasswordLineEdit->text())
        {
            qDebug() << "info - if: password ok? - OK";
            db.addUser(m_usernameLogin, m_passwordLogin);
            QSqlQuery query("SELECT * FROM users");
            if (query.exec()) {
                while (query.next()) {
                    QString username = query.value("username").toString();
                    QString password = query.value("password").toString();
                    qDebug() << "Użytkownik:" << username << ", Hasło:" << password;
                }
            } else {
                qDebug() << "Błąd zapytania SQL:" << query.lastError().text();
            }
            chatWindow.show();
            close();
        }
        else
            QMessageBox::warning(this,"Register","Niepoprawne Dane");
        db.closeconnection();
    }
    else
        QMessageBox::critical(this, "Register", "Błąd połączenia z bazą");
}

