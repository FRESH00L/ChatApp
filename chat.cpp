#include "chat.h"
#include "ui_chat.h"
#include "message.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <QMessageBox>
#include <QList>
Chat::Chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chat),socket(new QTcpSocket(this)),server(new QTcpServer(this))
{

    ui->setupUi(this);
    connect(socket,&QTcpSocket::readyRead, this, &Chat::reciveMessage);

}

Chat::~Chat()
{
    delete ui;
}

void Chat::sendMessage()
{
    Message* message = new Message();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    QString newMessage = ui->message->toPlainText();
    message->setMessage(newMessage);
    message->setDateTime(QDateTime::currentDateTime());

    // Set the username from the database
    message->setUsername(database.getCurrentUsername());qDebug() << "Username in sendMessage: " << message->getUsername();

    listOfMessages.append(message);

    out.setVersion(QDataStream::Qt_5_10);
    out << message->getUsername() << message->getDateTimeString() << newMessage;

    socket->write(block);

    ui->chat->clear();
    for (int i = 0; i < listOfMessages.size(); i++)
    {
        const Message* msg = listOfMessages.at(i);
        ui->chat->append(QString("%1 [%2]: %3").arg(msg->getDateTimeString(), msg->getUsername(), msg->getMessage()));
        qDebug() << i;
    }
    ui->message->clear();
    qDebug() << "sendMessage";
}

void Chat::reciveMessage()
{
    QString username, date, time, newMessage;
    qDebug() << "reciveMessage";
    QByteArray block;
    QDataStream in(socket);
    in >> username >> date >> time >> newMessage;
    ui->chat->append(QString("%1 [%2]: %3").arg(date, time, username, newMessage));
}

void Chat::startServer()
{
    if(server->isListening())
        QMessageBox::warning(this, "Serwer", "Server is already running");
    connect(server,&QTcpServer::newConnection, this, &Chat::connectToServer);
    qDebug() << "server is running on port: " << ui->portTextEdit->toPlainText().toInt();
}

void Chat::on_sendPushButton_clicked()
{
    qDebug() << "Current username before sendMessage: " << database.getCurrentUsername();
    sendMessage();
}

void Chat::connectToServer()
{
    socket->connectToHost(ui->IPTextEdit->toPlainText(), ui->portTextEdit->toPlainText().toInt());
    qDebug() << "connected";
}

void Chat::on_connectPushButton_clicked()
{
    startServer();
    connectToServer();
}
