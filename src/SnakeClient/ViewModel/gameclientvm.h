#ifndef GAMECLIENTVM_H
#define GAMECLIENTVM_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <set>
#include <clientmanager.h>

class GameClientVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 clientId READ clientId NOTIFY connected)
    Q_PROPERTY(qint16 roomId READ roomId NOTIFY enteredRoom)
    Q_PROPERTY(std::list<qint16> openRooms READ openRooms NOTIFY openRoomsChanged)

public:
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new GameClientVM;
    }

    /**d
     * @brief Attempts to connect the client to address on the given port.
     *
     * This method can be called from QML.
     * @param address
     * @param port
     */
    Q_INVOKABLE void connectToServer(QString address = "", qint16 port = 0);
    Q_INVOKABLE void createRoom();
    Q_INVOKABLE void joinRoom(qint16 roomId);
    Q_INVOKABLE void leaveRoom();
    Q_INVOKABLE void readyToPlay();
    Q_INVOKABLE void startGame();

    qint16 clientId() const { return m_clientManager.client()->clientId(); }
    qint16 roomId() const { return m_clientManager.roomId(); }
    const std::list<qint16> &openRooms() const { return m_clientManager.openRooms(); }

signals:
    void connected();
    void errorMessage(QString error);
    void enteredRoom();
    void openRoomsChanged();

private:
    explicit GameClientVM(QObject *parent = nullptr);

    ClientManager &m_clientManager;
};

#endif // GAMECLIENTVM_H
