#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <set>

/**
 * @brief The SocketServer provides a TCP-based server.
 *
 * This class is responsible for listening for incoming connections.
 */
class SocketServer : public QTcpServer
{
    Q_OBJECT
public:
    /**
     * @brief Cosntruct a SocketServer object
     */
    explicit SocketServer(QObject *parent = nullptr);

    /**
     * @brief Sends message to the specified client
     * @param message
     * @param clientId client ID
     */
    void sendMessageToClient(QByteArray message, qint16 clientId);

    /**
     * @brief Sends message to multiple clients
     * @param message
     * @param clients client IDs
     */
    void sendMessageToMultipleClients(QByteArray message, std::vector<qint16> clients);

signals:
    /**
     * @brief Emitted every time a new message has received.
     * @param message
     */
    void onNewMessageReceived(QByteArray message);

    /**
     * @brief Emitted every time a new client connected.
     * @param clientId client ID
     */
    void clientConnected(qint16 clientId);

    /**
     * @brief Emitted every time thr client disconnected
     * @param clientId client ID
     */
    void clientDisconnected(qint16 clientId);

public slots:
    /**
     * @brief This method is called when new client connects
     *
     * Adds new connection to the client list and prepare to read/write on the socket.
     * Creates a unique identifier for this connection and send it back to the client.
     * This slot is connected to QTcpServer::newConnection.
     */
    void onNewConnection();

    /**
     * @brief Reads chunk of data from the client
     *
     * This slot is connected to QTcpServer::readyRead.
     */
    void onReadyRead();

    /**
     * @brief Closes socket connection and remove it from the client lists
     *
     * This slot is connected to QTcpServer::disconected.
     */
    void onDisconected();

private:
    /**
     * @brief Collection of connected clients
     */
    std::map<qint16, QTcpSocket*> m_clients;
};

#endif // SOCKETSERVER_H
