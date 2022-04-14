#include "socketclient.h"

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
    QByteArray message = readAll();
    qDebug() << "Received message" << message;
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
}

void SocketClient::connectToServer(QString address, qint16 port)
{
    connectToHost(QHostAddress(address), port);
}
