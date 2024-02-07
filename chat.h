#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include "network.h"
#include "user.h"
#include <QListWidgetItem>
#include "database.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Chat; }
QT_END_NAMESPACE

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    Chat(QWidget *parent = nullptr);
    ~Chat();
    void setCurrentUsername(const QString& username);
    void setPort(int _port);
    void startServ(int);

private slots:
    void on_startServerButton_clicked();
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void handleMessageReceived(const QString &sender, const QString &message);

    void on_addNewFriendPushButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Chat *ui;
    Network *network;
    QString m_currentClient;
    QString m_currentUsername;
    QString formatMessage(const QString &username, const QString &message);
    QList<User> listOfUsers;
    int m_port;
};

#endif // CHAT_H
