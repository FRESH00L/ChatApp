#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);

    void setUsername(const QString &_username);
    void setDateTime(const QDateTime &_datetime);
    void setMessage(const QString &_message);

    QString getUsername() const;
    QString getDateTimeString() const;
    QString getMessage() const;

private:
    QString m_username;
    QDateTime m_datetime;
    QString m_message;
};

#endif // MESSAGE_H
