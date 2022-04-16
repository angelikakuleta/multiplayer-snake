#include "clientmanager.h"

ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    m_client = new SocketClient(this);
    m_board = new GameBoard(this);
}

ClientManager::~ClientManager()
{
    m_client->deleteLater();
    m_board->deleteLater();
}
