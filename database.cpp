#include "database.h"
#include "chat.h"
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

int DataBase::getPortFromUser(QString _username)
{

    QSqlQuery query;
    query.prepare("SELECT port FROM users WHERE username = :username");
    query.bindValue(":username",_username);
    if (query.exec()) {
        while (query.next()) {
            int port = query.value("port").toInt();
            qDebug() << "Port dla użytkownika freshol:" << port;
            return port;
        }
    } else {
        qDebug() << "Błąd zapytania SQL:" << query.lastError().text();
    }

}

void DataBase::closeconnection()
{
    db.close();
}

DataBase::~DataBase()
{
    closeconnection();
    qDebug() << "info - connection closed";
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
    QString ipAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(int i =0;i<ipAddressList.size();i++)
    {
        if(ipAddressList.at(i) != QHostAddress::LocalHost && ipAddressList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressList.at(i).toString();

            break;
        }
    }
    int port = rand()%10000;
    qDebug() << ipAddress;
    query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, ip TEXT, port INTEGER)");
    query.prepare("INSERT INTO users (username, password, ip, port) VALUES (:username, :password, :ip, :port)");
    query.bindValue(":username", _user);
    query.bindValue(":password", hashedPassword);
    query.bindValue(":ip", ipAddress);
    query.bindValue(":port", port);

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
        qDebug() << "info - Funkcja checkLogin - Close";
        return true;
    }
    else
    {
        qDebug() << "info - Funkcja checkLogin - Close";
        return false;
    }
}

QString DataBase::findNewFriend(QString _username)
{
    qDebug() << "info - findNewFriend - Open";
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", _username);

    if (!query.exec())
    {
        qDebug() << "Błąd wykonania zapytania:" << query.lastError().text();
        return 0;
    }

    QString userIp;
    while(query.next())
    {
        userIp = query.value("ip").toString();
    }
    return userIp;
}
