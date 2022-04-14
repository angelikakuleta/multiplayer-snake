#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QString>

const qint16 PORT = 8080;

const char BREAK_CHAR = '#';
const char* C_CLIENET_ID = "CID";

SocketServer::SocketServer(QObject *parent)
    : QTcpServer(parent)
{
    srand(time(NULL));

    if (listen(QHostAddress::Any, PORT)) {
        qDebug() << "Server is running on port" << PORT;
    } else {
        connect(this, &QTcpServer::newConnection, this, &SocketServer::onNewConnection);
        qDebug() << "Server fails to start";
    }

    connect(this, &QTcpServer::newConnection, this, &SocketServer::onNewConnection);
}

void SocketServer::sendMessageToClient(QByteArray message, qint16 clientId)
{
    if (m_clients.find(clientId) != m_clients.end())
    {
        QTcpSocket* existingClient = m_clients[clientId];
        existingClient->write(message);
    }
}

void SocketServer::onNewConnection()
{
    QTcpSocket *newClient = nextPendingConnection();
    newClient->setParent(this);

    connect(newClient, &QTcpSocket::readyRead, this, &SocketServer::onReadyRead);
    connect(newClient, &QTcpSocket::disconnected, this, &SocketServer::onDisconected);

    qint16 clientId;
    do {
        clientId =rand() % 8999 + 1000;
    } while (m_clients.find(clientId) != m_clients.end());

    m_clients[clientId] = newClient;

    QByteArray message;
    message.append(C_CLIENET_ID)
        .append(BREAK_CHAR)
        .append(QByteArray::number(clientId));
    newClient->write(message);

    qDebug() << "New client connected";
}

void SocketServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray message = sender->readAll();

    qDebug() << "Received new client message" << message;
    emit newMessageReceived(message);
}

void SocketServer::onDisconected()
{
    QTcpSocket* client = static_cast<QTcpSocket*>(QObject::sender());
    if (client) {
        for (auto mapIterator = m_clients.begin(); mapIterator != m_clients.end(); mapIterator++) {
            if (mapIterator->second == client)
                m_clients.erase(mapIterator->first);
        }
        client->deleteLater();
    }

    qDebug() << "Client disconnected";
}
