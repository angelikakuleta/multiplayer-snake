#include "gameroom.h"

GameRoom::GameRoom(qint16 roomId, QObject *parent)
    : QObject{parent},
    m_roomId(roomId)
{
    m_game = new GameEngine(this);
}

GameRoom::~GameRoom()
{
    m_game->deleteLater();
}

void GameRoom::addClient(qint16 clientId)
{
    if (utils::contain(m_clients, clientId))
        return;

    m_clients.push_back(clientId);
    m_readyList[clientId] = false;
}

void GameRoom::removeClient(qint16 clientId)
{
    m_game->removePlayer(clientId);
    if (utils::findAndRemove(m_clients, clientId))
        m_readyList.erase(clientId);
}

void GameRoom::readyToPlay(qint16 clientId)
{
    if (utils::contain(m_clients, clientId)) {
        m_readyList[clientId] = true;
        m_game->addPlayer(clientId);
    }
}

void GameRoom::startGame()
{
    for (auto &clientId : m_clients)
        if (m_readyList[clientId] == false) return;

    m_game->startGame();
}

void GameRoom::resetGame()
{
    if (!m_game->isRunning()) return;

    for (auto it = m_readyList.begin(); it != m_readyList.end(); ++it)
        it->second = false;
    m_game->resetGame();
}

const std::vector<qint16> GameRoom::readyClients() const
{
    std::vector<qint16> clients;
    for (auto it = m_readyList.begin(); it != m_readyList.end(); ++it)
        if (it->second == true) clients.push_back(it->first);

    return clients;
}

bool GameRoom::isOpen()
{
    return !m_game->isRunning() && m_clients.size() < m_game->maxPlayers();
}
