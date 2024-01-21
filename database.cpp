#include "database.h"
#include <QCryptographicHash>

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"info - Konstruktor DataBase - Open";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if(!openconnection())
        qDebug()<<"! -- Błąd połączenia z Bazą Danych " <<db.lastError().text();
    qDebug()<<"info - Konstruktor DataBase - Close";
}

QString DataBase::getCurrentUsername() const
{
    qDebug() << "info - getCurrentUsername - Returning: " << currentUsername;
    return currentUsername;
}

void DataBase::closeconnection()
{
    db.close();
}

DataBase::~DataBase()
{
    closeconnection();
}

bool DataBase::openconnection()
{
    qDebug() << "info - openconnection - Open";
    if (db.open())
    {
        qDebug() << "info - Połączenie z bazą danych otwarte.";
        return true;
    }
    else
    {
        qDebug() << "! -- Błąd otwierania połączenia z bazą danych:" << db.lastError().text();
        return false;
    }
}


void DataBase::addUser(QString _user, QString _password)
{
    qDebug() << "info - Funkcja addUser - Open";
    qDebug() << _user << " " << _password;
    QByteArray hashedPassword = QCryptographicHash::hash(_password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)");
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", _user);
    query.bindValue(":password", hashedPassword);
    if (!query.exec()) {
        qDebug() << "! -- Błąd dodawania użytkownika do bazy danych:" << query.lastError().text();
    }
    qDebug() << "info - Funkcja addUser - Close";
}

bool DataBase::checkLogin(const QString& _username, const QString& _password)
{
    qDebug() << "info - Funkcja checkLogin - Open";
    QByteArray hashedPassword = QCryptographicHash::hash(_password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", _username);
    query.bindValue(":password",hashedPassword);
    if(query.exec() && query.next())
    {
        currentUsername = _username;qDebug() << "info - Funkcja checkLogin - Username set: " << currentUsername;
        qDebug() << "info - Funkcja checkLogin - Close";
        return true;
    }
    else
    {
        qDebug() << "info - Funkcja checkLogin - Close";
        return false;
    }

}

