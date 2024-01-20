#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>
#include <QString>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    void setUsername(QString);
    void setDateTime(QDateTime);
    void setMessage(QString);
    QString getUsername();
    QString getDate();
    QString getTime();
    QString getMessage();

private:
    QString m_username;
    QString m_date;
    QString m_time;
    QString m_message;
signals:
};

#endif // MESSAGE_H
