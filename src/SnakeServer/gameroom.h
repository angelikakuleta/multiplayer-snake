#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <QObject>
#include <Snake/gameengine.h>
#include <utils.h>

class GameRoom : public QObject
{
    Q_OBJECT
public:
    explicit GameRoom(qint16 roomId, QObject *parent = nullptr);
    ~GameRoom();

    void addClient(qint16 clientId);
    void removeClient(qint16 clientId);
    void readyToPlay(qint16 clientId);
    bool isOpen();
    void startGame();
    void resetGame();

    qint16 roomId() const { return m_roomId; }
    GameEngine *game() const { return m_game; };
    const std::vector<qint16> clients() const { return m_clients; }
    const std::vector<qint16> readyClients() const;

signals:
    void roomListUpdated();
    void readyListUpdated(qint16 roomId);

private:
    qint16 m_roomId;
    std::vector<qint16> m_clients;
    std::map<qint16, bool> m_readyList;
    GameEngine *m_game;
};

#endif // GAMEROOM_H
