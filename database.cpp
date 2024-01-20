#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"konstruktor database";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
    if(!openconnection())
        qDebug()<<"Błąd połączenia z Bazą Danych... " <<db.lastError().text();

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

}


void DataBase::addUser(QString _user, QString _password)
{
    qDebug() << "addUser...";
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password");
    query.bindValue(":username", _user);
    query.bindValue(":password", _password);
    if (!query.exec()) {
        qDebug() << "Błąd dodawania użytkownika do bazy danych:" << query.lastError().text();
    }
    qDebug() << "addUser...end";
}

bool DataBase::checkLogin(QString _username, QString _password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", _username);
    query.bindValue(":password",_password);
    if(query.exec())
        return true;
    else
        return false;
}
