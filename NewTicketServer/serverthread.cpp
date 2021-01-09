#include "serverthread.h"
#include "QByteArray"
#include "QJsonDocument"
#include "QJsonObject"


serverThread::serverThread()
{

}

serverThread::serverThread(qintptr sockDesc) {
    this->socketptr = sockDesc;
}

void serverThread::run() {

    QTcpSocket socket;
    socket.setSocketDescriptor(this->socketptr);

    if(socket.waitForReadyRead()) {
  //      qDebug("收到客户端第一次请求");
        QByteArray inBytes = socket.readAll();

        QJsonDocument doc;
        doc = QJsonDocument::fromJson(inBytes);
        QJsonObject inJsonObj = doc.object();

        QJsonArray outJsonArray;
        service::getInstance()->handleRqst(inJsonObj, outJsonArray);

        doc.setArray(outJsonArray);
        QByteArray outBytes = QByteArray(doc.toJson());

        QJsonObject outJsonObj;
        outJsonObj.insert("length", outBytes.length());
        QJsonDocument doc2;
        doc2.setObject(outJsonObj);

        socket.write(doc2.toJson());
        socket.flush();

        if(socket.waitForReadyRead()) {

//            qDebug("收到客户端第二次请求");
            socket.readAll();

            socket.write(outBytes);
            socket.waitForBytesWritten();
            socket.flush();
        }
        else {
            qDebug("[Error] 服务器接收数据超时，发生在两次write之间");
        }
    }
    else {
        qDebug("[Error] 服务器接收数据超时，发生在客户端连接以后");
    }
}
