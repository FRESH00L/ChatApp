#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    bool openconnection();
    void closeconnection();
    void addUser(QString,QString);
    bool checkLogin(QString,QString);
private:

    QSqlDatabase db;

signals:
};

#endif // DATABASE_H
