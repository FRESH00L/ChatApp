#include "network.h"
#include "qmessagebox.h"
#include <QDebug>

Network::Network(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Network::handleNewConnection);
}

void Network::startServer()
{
    if (!tcpServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Error: " << tcpServer->errorString();
    } else {
        qDebug() << "Server started";
    }
}

void Network::connectToServer(const QString &ipAddress)
{
    QHostAddress address(ipAddress);
    QMessageBox msg;
    if (address.isNull() || ipAddress.isEmpty()) {
        msg.setText("Niepoprawny adres IP");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Network::readMessage);
    connect(tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    tcpSocket->connectToHost(ipAddress, 1234);

}

void Network::sendMessage(const QString &message)
{
    if (tcpSocket && tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(message.toUtf8());
    }
}

void Network::handleNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Network::readMessage);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
}

void Network::handleSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket Error: " << socketError;
}

void Network::readMessage()
{
    QString message = QString::fromUtf8(tcpSocket->readAll());
    emit messageReceived(tcpSocket->peerAddress().toString(), message);
}
