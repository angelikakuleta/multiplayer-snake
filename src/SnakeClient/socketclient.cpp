#include "socketclient.h"
#include <contract.h>

const char* DEFAULT_ADDRESS = "127.0.0.1";
const qint16 DEFAULT_PORT = 8080;

SocketClient::SocketClient(QObject *parent)
    : QTcpSocket{parent}
    , m_clientId(-1)
{
    connect(this, &QTcpSocket::connected, this, &SocketClient::onConnected);
    connect(this, &QTcpSocket::readyRead, this, &SocketClient::onReadyRead);
    connect(this, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this, SLOT(onError(QAbstractSocket::SocketError)));
}

void SocketClient::onConnected()
{
    qDebug() << "Connection established";
}

void SocketClient::onReadyRead()
{
    QByteArray data = readAll();
    for (auto &message : data.split(Contract::endChar())) {
        if (message.size() == 0) continue;
        qDebug() << "Received message" << message;
        emit newMessageReceived(message);
    }
}

void SocketClient::sendMessage(QByteArray message)
{
    message.append(Contract::endChar());
    write(message);
}

void SocketClient::onError(QAbstractSocket::SocketError error)
{
    QString errMessage;
    switch (error)
    {
        case QAbstractSocket::ConnectionRefusedError:
            errMessage = "Connection was refused";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            errMessage = "Remote host closed the connection";
            break;
        case QAbstractSocket::HostNotFoundError:
            errMessage = "Host address was not found.";
            break;
        case QAbstractSocket::SocketTimeoutError:
            errMessage = "Connection timed out";
            break;
        default:
            errMessage = "Unknown error";
    }

    qDebug() << "Received error" << errMessage;
    emit errorMessage(errMessage);
}

void SocketClient::connectToServer(QString address, qint16 port)
{
    if (address.length() == 0) address = DEFAULT_ADDRESS;
    if (port == 0) port = DEFAULT_PORT;

    connectToHost(QHostAddress(address), port);
}
