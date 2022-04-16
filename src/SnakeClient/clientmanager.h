#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "gameboard.h"
#include "messageparser.h"
#include "socketclient.h"
#include <QObject>

class ClientManager : public QObject
{
    Q_OBJECT

public:  
    ~ClientManager();

    static ClientManager& instance() {
        static ClientManager *instance = new ClientManager();
        return *instance;
    }

    SocketClient *client() const { return m_client; }
    GameBoard *board() const { return m_board; };
    void setBoard(GameBoard *newBoard) { m_board = newBoard; }

public slots:
    void onNewMessageReceived(QByteArray message);

private:
    explicit ClientManager(QObject *parent = nullptr);

    SocketClient* m_client;
    MessageParser* m_messageParser;
    GameBoard* m_board;
};

#endif // CLIENTMANAGER_H

