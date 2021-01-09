#include <QCoreApplication>
#include "server.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server* serv = new server();
    serv->listen(QHostAddress::Any, 9998);
    return a.exec();
}
