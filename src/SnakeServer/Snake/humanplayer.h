#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include <QObject>

class HumanPlayer : public Player
{
    Q_OBJECT
public:
    explicit HumanPlayer(qint16 playerId, Tile tile, QObject *parent = nullptr);


    // Player interface
public:
    Position move() override;
    void setDirection(const Direction &direction) override;
};

#endif // HUMANPLAYER_H
