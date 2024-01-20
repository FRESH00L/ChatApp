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
    listOfMessages.append(message);
    out.setVersion(QDataStream::Qt_5_10);
    out<<newMessage;
    socket->write(block);
    ui->chat->clear();
    for(int i =0;i<listOfMessages.size();i++)
    {
        ui->chat->append(listOfMessages.at(i)->getMessage());
        qDebug()<<i;
    }
    qDebug() << "sendMessage";
}

void Chat::reciveMessage()
{
    QString newMessage;
    qDebug() << "reciveMessage";
    QByteArray block;
    QDataStream in(socket);
    in>>newMessage;
    ui->chat->setText(newMessage);
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

