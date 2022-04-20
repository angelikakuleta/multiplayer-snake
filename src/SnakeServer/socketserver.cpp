#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <contract.h>
#include <QDebug>
#include <QString>

const qint16 PORT = 8080;

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
    message.append(Contract::endChar());
    if (m_clients.find(clientId) != m_clients.end())
    {
        QTcpSocket* existingClient = m_clients[clientId];
        existingClient->write(message);
    }
}

void SocketServer::sendMessageToMultipleClients(QByteArray message, std::vector<qint16> clients)
{
    for (auto &clientId : clients)
    {
        sendMessageToClient(message, clientId);
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

    qDebug() << "New client connected";
    emit clientConnected(clientId);
}

void SocketServer::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = sender->readAll();

    for (auto &message : data.split(Contract::endChar())) {
        if (message.size() == 0) continue;
        qDebug() << "Received new client message" << message;
        emit onNewMessageReceived(message);
    }
}

void SocketServer::onDisconected()
{
    QTcpSocket* client = static_cast<QTcpSocket*>(QObject::sender());

    if (client) {
        for (auto mapIterator = m_clients.begin(); mapIterator != m_clients.end(); mapIterator++) {
            if (mapIterator->second == client) {
                qint16 clientId = mapIterator->first;
                m_clients.erase(clientId);

                emit clientDisconnected(clientId);
                break;
            }
        }
        client->deleteLater();

        qDebug() << "Client disconnected";
    } 
}
