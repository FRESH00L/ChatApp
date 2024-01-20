#include "message.h"

Message::Message(QObject *parent)
    : QObject{parent}
{}

void Message::setUsername(QString _username)
{
    m_username = _username;
}

void Message::setDateTime(QDateTime _datetime)
{
    m_date = _datetime.date().toString();
    m_time = _datetime.time().toString();
}

void Message::setMessage(QString _message)
{
    m_message = _message;
}

QString Message::getUsername()
{
    return m_username;
}

QString Message::getDate()
{
    return m_date;
}

QString Message::getTime()
{
    return m_time;
}


QString Message::getMessage()
{
    return m_message;
}
