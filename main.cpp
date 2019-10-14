#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: server");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
                QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("1234"));
    parser.addOption(portOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);
    quint16 port = parser.value(portOption).toUShort();

    Server *server = new Server(port, debug);
    QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
