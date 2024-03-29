#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);

signals:
    void messageReceived(const QString &sender, const QString &message);

public slots:
    void startServer(int);
    void connectToServer(const QString &ipAddress, int port);
    void sendMessage(const QString &message);
    void handleNewConnection();
    void handleSocketError(QAbstractSocket::SocketError socketError);
    void readMessage();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // NETWORK_H
