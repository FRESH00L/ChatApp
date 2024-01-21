#include "database.h"

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

bool DataBase::checkLogin(QString _username, QString _password)
{
    qDebug() << "info - Funkcja checkLogin - Open";
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", _username);
    query.bindValue(":password",_password);
    if(query.exec() && query.next())
    {

        qDebug() << "info - Funkcja checkLogin - Close";
        return true;
    }
    else
    {
        qDebug() << "info - Funkcja checkLogin - Close";
        return false;
    }

}


void DataBase::addUser(QString _user, QString _password)
{

    qDebug() << "info - Funkcja addUser - Open";
    qDebug() << _user << " " << _password;
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)");
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", _user);
    query.bindValue(":password", _password);
    if (!query.exec()) {
        qDebug() << "! -- Błąd dodawania użytkownika do bazy danych:" << query.lastError().text();
    }
    qDebug() << "info - Funkcja addUser - Close";
}

