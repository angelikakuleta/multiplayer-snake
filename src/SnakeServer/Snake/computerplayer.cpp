#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(qint16 playerId, Tile tile, QObject *parent)
    : Player(playerId, tile, parent)
{
}

Position ComputerPlayer::move()
{
    return m_head;
}
