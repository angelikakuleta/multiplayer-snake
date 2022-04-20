#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <game.h>

using Tile = Game::Tile;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(qint16 clientId, Tile tile, QObject *parent = nullptr);

    qint16 clinetId() const { return m_clinetId; };
    Tile tile() const { return m_tile; }
    bool isReady() const { return m_isReady; };
    void setIsReady(bool newIsReady) { m_isReady = newIsReady; }
    int score() const { return m_score; };
    void setScore(int newScore) { m_score = newScore; }

private:
    qint16 m_clinetId;
    Tile m_tile;
    bool m_isReady;
    int m_score;
};

#endif // PLAYER_H
