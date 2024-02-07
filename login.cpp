#include "login.h"
#include "chat.h"
#include "ui_login.h"
#include "database.h"
#include <QMessageBox>
#include <QCryptographicHash>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->showPasswordCheckBox, &QCheckBox::toggled, this, &Login::on_showPasswordCheckBox_toggled);
    setFixedSize(size());
}

Login::~Login()
{
    delete ui;
}

bool Login::checkIfValid(QString _username, QString _password)
{
    QString checkIfBlankUsername = _username.simplified();
    QString checkIfBlankPassword = _password.simplified();
    if(checkIfBlankUsername == _username && checkIfBlankPassword == _password && _password.length() > 6)
        return true;
    return false;
}

QString Login::hashPassword(const QString& password)
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

void Login::on_signInPushButton_clicked()
{
    qDebug() << "info - Funkcja signIn - Open";
    m_usernameLogin = ui->usernameLoginLineEdit->text();
    QString enteredPassword = ui->passwordLoginLineEdit->text();
    QString hashedPassword = hashPassword(enteredPassword);


    DataBase db;
    if(db.openconnection())
    {
        qDebug() << "info - if: db.openconnection - OK";
        if(db.checkLogin(m_usernameLogin, hashedPassword))
        {
            qDebug() << "info - proper user - OK";
            QMessageBox::information(this, "Login", "Zalogowano pomyślnie.");
            QSqlQuery query("SELECT * FROM users");

            if (query.exec()) {
                while (query.next()) {
                    QString username = query.value("username").toString();
                    QString password = query.value("password").toString();
                    QString ip = query.value("ip").toString();
                    int port = query.value("port").toInt();
                    qDebug() << "Użytkownik: " << username << ", Hasło: " << password << ", IP: " << ip << ", port: " <<port;

                }
            } else {
                qDebug() << "! -- Błąd zapytania SQL:" << query.lastError().text();
            }
            int port = db.getPortFromUser(m_usernameLogin);
            qDebug() << m_usernameLogin << port;
            chatWindow.setPort(port);
            chatWindow.setCurrentUsername(m_usernameLogin);
            chatWindow.startServ(port);
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

    m_usernameLogin = ui->usernameRegisterLineEdit->text();
    QString enteredPassword = ui->passwordRegisterLineEdit->text();
    QString confirmedPassword = ui->checkPasswordLineEdit->text();

    if (enteredPassword == confirmedPassword)
    {
        QString hashedEnteredPassword = hashPassword(enteredPassword);

        QString hashedConfirmPassword = hashPassword(enteredPassword);
        DataBase db;
        if(db.openconnection())
        {
            qDebug() << "info - if: db.openconnection - OK";
            if(ui->passwordRegisterLineEdit->text() == ui->checkPasswordLineEdit->text())
            {
                if(checkIfValid(m_usernameLogin, enteredPassword))
                {
                    qDebug() << "info - if: password ok? - OK";
                    db.addUser(m_usernameLogin, hashedEnteredPassword);
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
                    int port = db.getPortFromUser(m_usernameLogin);
                    qDebug() << m_usernameLogin << port;
                    chatWindow.setPort(port);
                    chatWindow.setCurrentUsername(m_usernameLogin);
                    chatWindow.startServ(port);
                    chatWindow.show();
                    close();
                }
                else
                    QMessageBox::warning(this,"Register","Niepoprawne Dane");
            }
            else
                QMessageBox::warning(this,"Register","Niepoprawne Dane");
            db.closeconnection();
        }
        else
            QMessageBox::critical(this, "Register", "Błąd połączenia z bazą");
    }
    else
    {
        QMessageBox::warning(this, "Register", "Hasła nie są zgodne");
    }
}

void Login::on_showPasswordCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->passwordLoginLineEdit->setEchoMode(QLineEdit::Normal);
        ui->passwordRegisterLineEdit->setEchoMode(QLineEdit::Normal);
        ui->checkPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passwordLoginLineEdit->setEchoMode(QLineEdit::Password);
        ui->passwordRegisterLineEdit->setEchoMode(QLineEdit::Password);
        ui->checkPasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void Login::on_passwordLoginLineEdit_textChanged(const QString &Arg1)
{
    ui->passwordLoginLineEdit->setEchoMode(QLineEdit::Password);
}

void Login::on_passwordRegisterLineEdit_textChanged(const QString &Arg1)
{
    ui->passwordRegisterLineEdit->setEchoMode(QLineEdit::Password);
}

void Login::on_checkPasswordLineEdit_textChanged(const QString &Arg1)
{
    ui->checkPasswordLineEdit->setEchoMode(QLineEdit::Password);
}
