#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "socketclient.h"

#include <QObject>

class ClientManager : public QObject
{
    Q_OBJECT

public:
    explicit ClientManager(QObject *parent = nullptr);
    ~ClientManager();

private:
    SocketClient* m_client;
};

#endif // CLIENTMANAGER_H
