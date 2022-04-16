#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>

/**
 * @brief The SocketClient provides a TCP socket.
 *
 * This class allows to establish a TCP connection and transfer streams of data.
 */
class SocketClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent);

    /**
     * @brief Attempts to make a connection to address on the given port.
     * @param address
     * @param port
     */
    void connectToServer(QString address, qint16 port);

    /**
     * @return #m_clientId
     */
    qint16 clientId() { return m_clientId; }

    /**
     * @param [in] #m_clientId
     */
    void setClientId(qint16 clientId) { if(m_clientId == -1) m_clientId = clientId; }

public slots:
    /**
     * @brief Invoked when connection has been successfully established.
     *
     * This slot is connected to QTcpSocket::connected.
     */
    void onConnected();

    /**
     * @brief Read all available data when new data has arrived.
     *
     * This slot is connected to QTcpSocket::readyRead.
     */
    void onReadyRead();

    /**
     * @brief Handles error when it has occurred.
     *
     * Checks error type and emits appropriate error message.
     * This slot is connected to QTcpSocket::errorOccurred.
     * @param error type of error that occurred
     */
    void onError(QAbstractSocket::SocketError error);

signals:
    /**
     * @brief Emitted every time a new message has received.
     * @param message
     */
    void newMessageReceived(QByteArray message);

    /**
     * @brief Emitted every time an error message has received.
     * @param errMessage error message
     */
    void errorMessage(QString errMessage);

private:
    /**
     * @brief The client ID
     */
    qint16 m_clientId;
};

#endif // SOCKETCLIENT_H
