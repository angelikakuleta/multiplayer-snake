#ifndef GAMECLIENTVM_H
#define GAMECLIENTVM_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <clientmanager.h>

class GameClientVM : public QObject
{
    Q_OBJECT

public:
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);

        return new GameClientVM;
    }

    /**
     * @brief Attempts to connect the client to address on the given port.
     *
     * This method can be called from QML.
     * @param address
     * @param port
     */
    Q_INVOKABLE void connectToServer(QString address = "", qint16 port = 0);

signals:
    void connected();
    void errorMessage(QString error);

private:
    explicit GameClientVM(QObject *parent = nullptr);

    ClientManager &m_clientManager;
};

#endif // GAMECLIENTVM_H
