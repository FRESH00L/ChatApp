#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent}
{}

void Message::setUsername(const QString &_username)
{
    m_username = _username;
}

void Message::setDateTime(const QDateTime &_datetime)
{
    m_datetime = _datetime;
}

void Message::setMessage(const QString &_message)
{
    m_message = _message;
}

QString Message::getUsername() const
{
    return m_username;
}

QString Message::getDateTimeString() const
{
    return m_datetime.toString("yyyy-MM-dd hh:mm:ss");
}

QString Message::getMessage() const
{
    return m_message;
}
