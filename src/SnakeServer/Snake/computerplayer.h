#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"
#include <QObject>

class ComputerPlayer : public Player
{
    Q_OBJECT
public:
    explicit ComputerPlayer(qint16 playerId, Tile tile, QObject *parent = nullptr);

    // Player interface
public:
    Position move() override;
};

#endif // COMPUTERPLAYER_H
