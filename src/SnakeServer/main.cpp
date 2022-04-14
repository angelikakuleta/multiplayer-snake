#include "socketserver.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SocketServer server;

    return a.exec();
}
