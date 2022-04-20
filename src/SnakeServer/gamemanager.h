#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "socketserver.h"
#include "messageparser.h"
#include "gameroom.h"

/**
 * @brief The GameManager class controlls data flow between server and clients
 */
class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

    void createRoomRequest(qint16 clientId);
    void joinRoomRequest(qint16 clientId, qint16 roomId);
    void leaveRoomRequest(qint16 clientId, qint16 roomId);
    void readyToPlayRequest(qint16 clientId, qint16 roomId);
    void startGameRequest(qint16 clientId, qint16 roomId);
    void changeDirectionRequest(qint16 clientId, qint16 roomId, GameEngine::Direction direction);

    void roomListUpdated();
    void readyListUpdated(qint16 roomId);

public slots:
    void onClientConnected(qint16 clientId);
    void onNewMessageReceived(QByteArray message);

private:
    SocketServer* m_socketServer;
    MessageParser* m_messageParser;
    std::map<qint16, GameRoom*> m_rooms;
    std::vector<qint16> m_clientInLobby;

    /**
     * @brief Checks if the client is assigned to any room
     * @param clientId client Id
     * @return room ID if found, -1 otherwise
     */
    qint16 findRoomByClient(qint16 clientId);

};

#endif // GAMEMANAGER_H
