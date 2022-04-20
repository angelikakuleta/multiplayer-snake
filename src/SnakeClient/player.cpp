#include "player.h"

Player::Player(qint16 clientId, Tile tile, QObject *parent)
    : QObject{parent}
    , m_clinetId(clientId)
    , m_tile(tile)
    , m_isReady(false)
    , m_score(0)
{
}
