#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "gameboard.h"
#include "messageparser.h"
#include "player.h"
#include "socketclient.h"
#include <QObject>
#include <set>

using Direction = Game::Direction;

class ClientManager : public QObject
{
    Q_OBJECT

public:  
    ~ClientManager();

    static ClientManager& instance() {
        static ClientManager *instance = new ClientManager();
        return *instance;
    }

    void createRoomRequest();
    void joinRoomRequest(qint16 roomId);
    void leaveRoomRequest();
    void readyToPlayRequest();
    void startGameRequest();
    void changeDirectionRequest(Direction direction);

    SocketClient *client() const { return m_client; }
    const std::list<qint16> &openRooms() const { return m_openRooms; }
    qint16 roomId() const { return m_roomId; }
    const std::vector<Player*> &players() const { return  m_players; }
    GameBoard *board() const { return m_board; };
    void setBoard(GameBoard *newBoard) { m_board = newBoard; }
    const Direction &direction() const { return m_direction; }
    void setDirection(const Direction &direction);    

public slots:
    void onNewMessageReceived(QByteArray message);

signals:
    void errorMessage(QString error);
    void connected();
    void enteredRoom();
    void openRoomsChanged();
    void playersChanged();

private:
    explicit ClientManager(QObject *parent = nullptr);

    SocketClient* m_client;
    MessageParser* m_messageParser;

    std::list<qint16> m_openRooms;
    qint16 m_roomId;
    std::vector<Player*> m_players;
    GameBoard* m_board;  
    Direction m_direction;
};

#endif // CLIENTMANAGER_H

