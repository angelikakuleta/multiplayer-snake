#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "gameboard.h"
#include "messageparser.h"
#include "socketclient.h"
#include <QObject>
#include <set>

class ClientManager : public QObject
{
    Q_OBJECT

public:  
    ~ClientManager();

    enum Direction {
        None = 0,
        Up,
        Down,
        Left,
        Right
    };
    Q_ENUM(Direction);

    static ClientManager& instance() {
        static ClientManager *instance = new ClientManager();
        return *instance;
    }

    void createRoomRequest();
    void joinRoomRequest(qint16 roomId);
    void leaveRoomRequest();
    void readyToPlayRequest();
    void startGameRequest();

    SocketClient *client() const { return m_client; }
    const std::list<qint16> &openRooms() const { return m_openRooms; }
    qint16 roomId() const { return m_roomId; }
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

private:
    explicit ClientManager(QObject *parent = nullptr);

    SocketClient* m_client;
    MessageParser* m_messageParser;

    std::list<qint16> m_openRooms;
    qint16 m_roomId;
    GameBoard* m_board;
    Direction m_direction;
};

#endif // CLIENTMANAGER_H

