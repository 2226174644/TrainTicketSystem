#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>

class server : public QTcpServer
{
public:
    server();
    void incomingConnection(qintptr sockDesc) override;
};

#endif // SERVER_H
