#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include<QDebug>


class Client
{
private:
    Client();
    static Client *cli;
    QTcpSocket socket;
    void connectServer();
    void disconnectServer();

public:
    ~Client();
    static Client* GetInstance();
    bool receiveData(QJsonArray &dataIn);
    bool sendData(QJsonObject &dataOut);
    bool handleData(QJsonObject &dataOut,QJsonArray &dataIn);

};

#endif // CLIENT_H
