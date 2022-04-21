#include "gameengine.h"
#include "humanplayer.h"
#include <QDebug>

const int GAME_SPEED = 500;
const int GAME_TIME = 300000;

const ushort GameEngine::s_maxPlayers = 4;

GameEngine::GameEngine(QObject *parent)
    : QObject{parent}
    , m_board()
    , m_isRunning(false)
{
    connect(&m_loopTimer, SIGNAL(timeout()), this, SLOT(onLoopIteration()));
}

void GameEngine::addPlayer(qint16 playerId, Tile tile)
{
    if (m_players.size() == s_maxPlayers) return;

    m_players[playerId] = new HumanPlayer(playerId, tile, this);
}

void GameEngine::removePlayer(qint16 playerId)
{
    if (isRunning()) return;
    if (m_players.find(playerId) == m_players.end()) return;

    m_players[playerId]->deleteLater();
    m_players.erase(playerId);
}

void GameEngine::startGame()
{
    if (isRunning()) return;
    if (m_players.size() <= 1) return;
        // add ComputerPlayer

    initialize();

    m_loopTimer.start(GAME_SPEED);
    QTimer::singleShot(GAME_TIME, this, SLOT(stopGame()));
}

void GameEngine::stopGame()
{
    m_loopTimer.stop();
    m_isRunning = false;
}

void GameEngine::resetGame()
{
    if (isRunning()) return;
        stopGame();

    for (auto &player : m_players)
        player.second->deleteLater();
    m_players.clear();
    m_board->clear();
}

void GameEngine::changeDirection(qint16 player, Direction direction)
{
    if (m_players.find(player) == m_players.end()) return;
    m_players[player]->setDirection(direction);
}

qint16 GameEngine::checkWinner()
{
    return -1;
}

void GameEngine::onLoopIteration()
{
    for (auto &player : m_players) {
        player.second->move();
        emit tick(m_board->tiles());
    }
}

void GameEngine::onStopGameRequest()
{
    stopGame();
}

void GameEngine::initialize()
{
    for (auto &player : m_players)
    {
        auto position = m_board->generatePlayer(player.second->tile());
        player.second->setHead(position);
        m_board->generateFood();
    }
}
