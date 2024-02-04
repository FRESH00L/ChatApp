#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include "network.h"

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

private slots:
    void on_startServerButton_clicked();
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void handleMessageReceived(const QString &sender, const QString &message);

private:
    Ui::Chat *ui;
    Network *network;
    QString m_currentUsername;
    QString formatMessage(const QString &username, const QString &message);
};

#endif // CHAT_H
