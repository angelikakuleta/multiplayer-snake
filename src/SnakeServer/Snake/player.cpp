#include "player.h"

Player::Player(qint16 playerId, Tile tile, QObject *parent)
    : QObject{parent}
    , m_playerId(playerId)
    , m_head({ 0, 0 })
    , m_direction(Direction::None)
    , m_tile(tile)
    , m_score(0)
{
    // for test
    m_direction = Direction::Right;
}

void Player::setDirection(const Direction &direction)
{
    m_direction = direction;
}

bool Player::isMoving()
{
    return m_direction != Direction::None;
}

void Player::setHead(const Position &head)
{
    if (m_body.size() == 0)
        m_head = head;
}
