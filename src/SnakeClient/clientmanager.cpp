#include "clientmanager.h"

const char* DEFAULT_ADDRESS = "127.0.0.1";
const qint16 DEFAULT_PORT = 8080;

ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    m_client = new SocketClient(this);
    m_client->connectToServer(DEFAULT_ADDRESS, DEFAULT_PORT);
}

ClientManager::~ClientManager()
{
    m_client->deleteLater();
}
