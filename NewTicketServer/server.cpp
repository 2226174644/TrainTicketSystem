#include "server.h"
#include "serverthread.h"

server::server()
{

}

void server::incomingConnection(qintptr sockDesc) {
    qDebug("[Debug] 监听到新的连接！");
    serverThread* newThread = new serverThread(sockDesc);
    connect(newThread, &serverThread::finished, newThread, &QThread::deleteLater);
    newThread->start();
}
