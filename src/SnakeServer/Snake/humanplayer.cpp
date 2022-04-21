#include "humanplayer.h"

HumanPlayer::HumanPlayer(qint16 playerId, Tile tile, QObject *parent)
    : Player(playerId, tile, parent)
{
}

Position HumanPlayer::move()
{
    if (isMoving() && m_body.size() > 0) {
        m_body.push_front(m_head);
        m_body.pop_back();
    }

    switch (m_direction) {
    case Direction::Up:
        m_head = { m_head.row - 1, m_head.column };
        break;
    case Direction::Down:
        m_head = { m_head.row + 1, m_head.column };
        break;
    case Direction::Left:
        m_head = { m_head.row, m_head.column - 1 };
        break;
    case Direction::Right:
        m_head = { m_head.row, m_head.column + 1 };
    default:
        break;
    }

    return m_head;
}

void HumanPlayer::setDirection(const Direction &direction)
{
    if (m_direction != direction)
        m_direction = direction;
}
