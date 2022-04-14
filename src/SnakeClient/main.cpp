#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "clientmanager.h"
#include "gameboard.h"
#include <ViewModel/gameboardvm.h>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<GameBoard>("GameBoard.Tile", 1, 0, "Tile", "Type of tile on the game board");

    auto board = GameBoard();
    auto boardVM = new GameBoardVM(&board);

    engine.rootContext()->setContextProperty("GameBoardVM", boardVM);

    ClientManager clientManager;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    return app.exec();
}
