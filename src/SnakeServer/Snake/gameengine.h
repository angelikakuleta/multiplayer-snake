#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTimer>
#include "gameboard.h"
#include "player.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = nullptr);

    static ushort maxPlayers() { return s_maxPlayers; }
    bool isRunning() const { return m_isRunning; };

    void addPlayer(qint16 playerId, Tile tile);
    void removePlayer(qint16 playerId);
    void startGame();
    void stopGame();
    void resetGame();
    void changeDirection(qint16 playerId, Direction direction);
    qint16 checkWinner();

signals:
    void tick(std::vector<Tile> tiles);

private slots:
    void onLoopIteration();
    void onStopGameRequest();

private:
    static const ushort s_maxPlayers;
    std::map<qint16, Player*> m_players;
    GameBoard *m_board;
    bool m_isRunning;
    QTimer m_loopTimer;

    void initialize();
};

#endif // GAMEENGINE_H
