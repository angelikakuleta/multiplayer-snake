#include "gameengine.h"

GameEngine::GameEngine(QObject *parent)
    : QObject{parent}
    , m_isRunning(false)
{
}

void GameEngine::addPlayer(qint16 player)
{
}

void GameEngine::removePlayer(qint16 player)
{
}

void GameEngine::startGame()
{
}

void GameEngine::resetGame()
{
}

void GameEngine::changeDirection(qint16 player, Direction direction)
{
}

qint16 GameEngine::checkWinner()
{
    return -1;
}

const ushort GameEngine::s_maxPlayers = 4;
