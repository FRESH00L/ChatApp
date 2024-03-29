#include "network.h"
#include <QErrorMessage>
#include <QDebug>


Network::Network(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Network::handleNewConnection);
}

void Network::startServer(int port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Error: " << tcpServer->errorString();
    } else {
        qDebug() << "Server started";
    }
}

void Network::connectToServer(const QString &ipAddress, int port)
{
    QHostAddress address(ipAddress);
    if (address.isNull() || ipAddress.isEmpty()) {
        QErrorMessage errorMessage;
        errorMessage.showMessage("Invalid IP Address");
        errorMessage.exec();
        return;
    }

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Network::readMessage);
    connect(tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError))); // Poprawione połączenie
    tcpSocket->connectToHost(ipAddress, port);

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
