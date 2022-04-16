#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ViewModel/gameboardvm.h>
#include <ViewModel/gameclientvm.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ClientManager::instance();

    qmlRegisterSingletonType<GameClientVM>("Snake.GameClient", 1, 0, "GameClient", &GameClientVM::qmlInstance);
    qmlRegisterType<GameBoardVM>("Snake.GameBoard", 1, 0, "GameBoard");

    qmlRegisterUncreatableType<GameBoard>("Snake.GameBoard.Tile", 1, 0, "Tile", "Type of tile on the game board");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    return app.exec();
}
