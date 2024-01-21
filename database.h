#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Login;
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    bool openconnection();
    void closeconnection();
    void addUser(QString,QString);
    bool checkLogin(const QString& _username, const QString& _password);
    QString getCurrentUsername() const;
private:
    QString currentUsername;
    QSqlDatabase db;


signals:
};

#endif // DATABASE_H
