#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include "message.h"
#include "database.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class Chat;
}
QT_END_NAMESPACE

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    Chat(QWidget *parent = nullptr);
    ~Chat();




private slots:
    void sendMessage();
    void reciveMessage();
    void startServer();
    void connectToServer();

    void on_sendPushButton_clicked();
    void on_connectPushButton_clicked();

private:
    Ui::Chat *ui;
    QTcpSocket *socket = nullptr;
    QTcpServer * server = nullptr;
    QList<Message*> listOfMessages;
    DataBase database;
};
#endif // CHAT_H
