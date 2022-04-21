#include "humanplayer.h"

HumanPlayer::HumanPlayer(qint16 playerId, Tile tile, QObject *parent)
    : Player(playerId, tile, parent)
{
}

Position HumanPlayer::move()
{
    return m_head;
}

void HumanPlayer::setDirection(const Direction &direction)
{
    if (m_direction != direction)
        m_direction = direction;
}
