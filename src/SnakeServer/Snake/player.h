#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <game.h>
#include <list>

using Direction = Game::Direction;
using Tile = Game::Tile;
using Position = Game::Position;
/**
 * @brief Aabstract class for all types of player
 */
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(qint16 playerId, Tile tile, QObject *parent = nullptr);

    virtual Position move() = 0;
    virtual void setDirection(const Direction &direction);
    bool isMoving();

    qint16 score() const { return m_score; }
    const Tile &tile() const { return m_tile; };
    const Position &head() const { return m_head; }
    void setHead(const Position &nhead);
    const Direction &direction() const { return m_direction; }

protected:
    qint16 m_playerId;
    Position m_head;
    std::list<Position> m_body;
    Direction m_direction;
    Tile m_tile;
    qint16 m_score;
};

#endif // PLAYER_H
