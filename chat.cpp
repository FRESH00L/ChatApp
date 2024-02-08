#include "chat.h"
#include "ui_chat.h"
#include <QMessageBox>
#include <QDateTime>
#include "database.h"

Chat::Chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chat)
{
    ui->setupUi(this);
    network = new Network(this);
    connect(network, &Network::messageReceived, this, &Chat::handleMessageReceived);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::setCurrentUsername(const QString &username)
{
    m_currentUsername = username;
    ui->usernameLabel->setText(username);
}

void Chat::startServ()
{
    network->startServer();
}

void Chat::on_connectButton_clicked()
{
    QString ipAddress = ui->IPLineEdit->text();
    network->connectToServer(ipAddress);
}

QString Chat::formatMessage(const QString &username, const QString &message)
{
    QString formattedMessage = QString("%1 [%2]: %3").arg(username).arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")).arg(message);
    return formattedMessage;
}

void Chat::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();

    QString formattedMessage = formatMessage(m_currentUsername, message);
    network->sendMessage(formattedMessage);
    ui->chatTextEdit->append(formattedMessage);
    ui->messageLineEdit->clear();
}

void Chat::handleMessageReceived(const QString &message)
{
    ui->chatTextEdit->append(message);
}

void Chat::on_addNewFriendPushButton_clicked()
{
    ui->listWidget->clear();
    DataBase db;
    QString newFriendUsername = ui->addNewFriendTextEdit->toPlainText();
    QString newFriendIP = db.findNewFriend(newFriendUsername);
    qDebug() << newFriendIP;
    QMessageBox msg;
    if(newFriendIP == "")
    {
        msg.setText("Nie znaleziono takiego użytkownika");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else
    {
    QString information = QString("Dodano użytkownika %1 o adresie ip: %2 do listy kontaktów").arg(newFriendUsername).arg(newFriendIP);
    msg.setInformativeText(information);
    msg.setIcon(QMessageBox::Information);
    msg.exec();

    User newFriend(newFriendUsername,newFriendIP);
    bool isOnList = false;
    for(int j = 0; j<ui->listWidget->count();j++)
    {
        QListWidgetItem* Item = ui->listWidget->item(j);
        if(Item->text() == newFriendUsername)
            isOnList = true;
    }
    if(!isOnList)
    {
        listOfUsers.append(newFriend);
        for(int i =0;i<listOfUsers.size();i++)
        {

        QString info = listOfUsers.at(i).m_username + ": " + listOfUsers.at(i).m_ip;
        QListWidgetItem *Item = new QListWidgetItem(info);
        Item->setData(Qt::UserRole, QVariant::fromValue(listOfUsers.at(i)));
        ui->listWidget->addItem(Item);
        ui->listWidget->show();
        }
    }
    }
    ui->addNewFriendTextEdit->clear();
}

void Chat::on_listWidget_itemClicked(QListWidgetItem *item)
{
    DataBase db;
    QString selectedItem = item->text();
    QStringList parts = selectedItem.split(":");
    QString friendUsername = parts[0];
    QString friendIP = parts[1];
    qDebug() << friendUsername << " " <<friendIP;
    m_currentClient = friendUsername;
    network->connectToServer(friendIP);
    ui->chatTextEdit->clear();
}


