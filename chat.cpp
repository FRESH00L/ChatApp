#include "chat.h"
#include "ui_chat.h"
#include <QMessageBox>
#include <QDateTime>

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

void Chat::on_startServerButton_clicked()
{
    network->startServer();
}

void Chat::on_connectButton_clicked()
{
    QString ipAddress = ui->IPLineEdit->text();
    int port = ui->portLineEdit->text().toInt();
    network->connectToServer(ipAddress, port);
}

QString Chat::formatMessage(const QString &username, const QString &message)
{
    QString formattedMessage = QString("[%1 - %2] %3").arg(username).arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")).arg(message);
    return formattedMessage;
}

void Chat::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();
    network->sendMessage(message);

    QString formattedMessage = formatMessage("Ja", message); // Tutaj używamy "Ja" jako nazwy użytkownika dla wysłanych wiadomości
    ui->chatTextEdit->append(formattedMessage);

    // Czyszczenie pola tekstowego po wysłaniu wiadomości
    ui->messageLineEdit->clear();
}

void Chat::handleMessageReceived(const QString &sender, const QString &message)
{
    QString formattedMessage = formatMessage(sender, message);
    ui->chatTextEdit->append(formattedMessage);
}
