#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_socketServer = new SocketServer(this);
    m_messageParser = new MessageParser(this);
    connect(m_socketServer, SIGNAL(clientConnected(qint16)),
            this, SLOT(onClientConnected(qint16)));
    connect(m_socketServer, SIGNAL(onNewMessageReceived(QByteArray)),
            this, SLOT(onNewMessageReceived(QByteArray)));
}

GameManager::~GameManager()
{
    m_socketServer->deleteLater();
    m_messageParser->deleteLater();
}

void GameManager::onClientConnected(qint16 clientId)
{
    QList<QByteArray> params;
    params.append(QByteArray::number(clientId));
    auto message = m_messageParser->buildMessage(Command::ClientRegistered, params);

    m_socketServer->sendMessageToClient(message, clientId);
}

void GameManager::onNewMessageReceived(QByteArray message)
{
    Command cmd;
    qint16 clientId;
    QList<QByteArray> params;

    bool isValid = false;

    isValid = m_messageParser->parseMessage(message, cmd, clientId, params);
    if (!isValid) return;

    switch (cmd) {
    case Command::StartGame:
        break;
    }
}
