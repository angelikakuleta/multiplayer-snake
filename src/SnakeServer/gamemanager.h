#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "socketserver.h"
#include "messageparser.h"

/**
 * @brief The GameManager class controlls data flow between server and clients
 */
class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();

public slots:
    void onClientConnected(qint16 clientId);
    void onNewMessageReceived(QByteArray message);

private:
    SocketServer* m_socketServer;
    MessageParser* m_messageParser;
};

#endif // GAMEMANAGER_H
