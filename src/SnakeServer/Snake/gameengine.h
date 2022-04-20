#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);

    enum Direction {
        None = 0,
        Up,
        Down,
        Left,
        Right
    };

    static ushort maxPlayers() { return s_maxPlayers; }
    bool isRunning() const { return m_isRunning; };

    void addPlayer(qint16 player);
    void removePlayer(qint16 player);
    void startGame();
    void resetGame();
    void changeDirection(qint16 player, Direction direction);
    qint16 checkWinner();

private:
    static const ushort s_maxPlayers;
    bool m_isRunning;
};

#endif // GAMEENGINE_H
