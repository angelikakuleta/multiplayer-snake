#include "gameclientvm.h"

GameClientVM::GameClientVM(QObject *parent)
    : QObject{parent}
    , m_clientManager(ClientManager::instance())
{
    connect(m_clientManager.client(), SIGNAL(errorMessage(QString)), this, SIGNAL(errorMessage(QString)));
    connect(&m_clientManager, SIGNAL(errorMessage(QString)), this, SIGNAL(errorMessage(QString)));
    connect(&m_clientManager, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(&m_clientManager, SIGNAL(enteredRoom()), this, SIGNAL(enteredRoom()));
    connect(&m_clientManager, SIGNAL(openRoomsChanged()), this, SIGNAL(openRoomsChanged()));
}

void GameClientVM::connectToServer(QString address, qint16 port)
{
    m_clientManager.client()->connectToServer(address, port);
}

void GameClientVM::createRoom()
{
    m_clientManager.createRoomRequest();
}

void GameClientVM::joinRoom(qint16 roomId)
{
    m_clientManager.joinRoomRequest(roomId);
}

void GameClientVM::leaveRoom()
{
    m_clientManager.leaveRoomRequest();
}

void GameClientVM::readyToPlay()
{
    m_clientManager.readyToPlayRequest();
}

void GameClientVM::startGame()
{
    m_clientManager.startGameRequest();
}
