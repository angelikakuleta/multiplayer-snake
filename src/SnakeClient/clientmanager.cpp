#include "clientmanager.h"

using ClientCmd = Contract::ClientCmd;
using ServerCmd = Contract::ServerCmd;

ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    m_client = new SocketClient(this);
    m_messageParser = new MessageParser(this);
    m_board = new GameBoard(this);

    connect(m_client, SIGNAL(newMessageReceived(QByteArray)),
                this, SLOT(onNewMessageReceived(QByteArray)));
}

ClientManager::~ClientManager()
{
    m_client->deleteLater();
    m_board->deleteLater();
}

void ClientManager::onNewMessageReceived(QByteArray message)
{
    Contract::ServerCmd cmd;
    QList<QByteArray> params;

    bool isValid = false;

    isValid = m_messageParser->parseMessage(message, cmd, params);
    if (!isValid) return;

    switch (cmd) {
    case ServerCmd::ClientIdRegistered:
        if (params.length() == 0) return;
        qint16 newClientId = params.first().toInt(&isValid);
        if (!isValid) return;
        m_client->setClientId(newClientId);
        break;
    }
}
