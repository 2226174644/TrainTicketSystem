#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include "server.h"
#include "QJsonArray"
#include "service.h"

class serverThread : public QThread
{
public:
    serverThread();
    serverThread(qintptr sockDesc);
    void run() override;
private:
    qintptr socketptr;
};

#endif // SERVERTHREAD_H
