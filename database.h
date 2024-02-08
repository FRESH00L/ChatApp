#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QHostAddress>
#include <QtNetwork/QNetworkInterface>

class Login;
class DataBase : public QObject
{
    Q_OBJECT
signals:

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    bool openconnection();
    void closeconnection();
    void addUser(QString,QString);
    bool checkLogin(const QString& _username, const QString& _password);
    int getPortFromUser(QString _username);
    QString getIPFromUser(QString _username);
    QString findNewFriend(QString);
private:
    QString currentUsername;
    QSqlDatabase db;


signals:
};

#endif // DATABASE_H
