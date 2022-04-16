#include "gameclientvm.h"

GameClientVM::GameClientVM(QObject *parent)
    : QObject{parent}
    , m_clientManager(ClientManager::instance())
{
    connect(m_clientManager.client(), SIGNAL(connected()), this, SIGNAL(connected()));
    connect(m_clientManager.client(), SIGNAL(errorMessage(QString)), this, SIGNAL(errorMessage(QString)));
}

void GameClientVM::connectToServer(QString address, qint16 port)
{
    m_clientManager.client()->connectToServer(address, port);
}
