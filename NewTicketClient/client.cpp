#include "client.h"
Client* Client::cli=new Client();
 Client::Client()
{

}
Client* Client::GetInstance(){
    return cli;
}
void Client::connectServer(){
    qDebug("连接测试");
    if(socket.isOpen()){
        socket.abort();
    }//终止之前的连接，重置套接字。
    socket.connectToHost("127.0.0.1",9998);
    if(socket.waitForConnected()){
         qDebug("连接服务器成功");
    }else {
         qDebug("连接服务器失败");
}
}
void Client::disconnectServer(){
    socket.close();
}
bool Client::receiveData(QJsonArray &dataIn){
    if(socket.waitForReadyRead()){//在一定时间内是否有数据传入
       //先读长度 length
        QByteArray lengthBuffer=socket.readAll();
        QJsonObject dataLength=QJsonDocument::fromJson(lengthBuffer).object();
        int allLength =dataLength.value("length").toInt();
        //再按长度读传入数据 while  .append(socket)
        //发送确认信息
        bool confirmFlag=true;
        QJsonObject confirm;
        confirm.insert("flag",confirmFlag);
        QByteArray confirmArray=QJsonDocument(confirm).toJson();
        socket.write(confirmArray);
        if(socket.waitForReadyRead()){
            QByteArray dataBuffer=socket.readAll();
            while(dataBuffer.length()<allLength){
               dataBuffer.append(socket.readAll());
           }
          dataIn=QJsonDocument::fromJson(dataBuffer).array();
        }
         return true;
    }

    else {
        qDebug("出错");
         return false;
    }
}
bool Client::sendData(QJsonObject &outData){
    qDebug("发送信息");
    QByteArray outBuffer=QJsonDocument(outData).toJson();
      socket.write(outBuffer);
      return true;
}

bool Client::handleData(QJsonObject &dataOut, QJsonArray &dataIn)
{   //连接
    qDebug("连接测试");
    if(socket.isOpen()){
        socket.abort();
    }//终止之前的连接，重置套接字。
    socket.connectToHost("127.0.0.1",9998);
    if(socket.waitForConnected()){
         qDebug("连接服务器成功");
         //发送信息
         qDebug("发送信息");
         QByteArray outBuffer=QJsonDocument(dataOut).toJson();
           socket.write(outBuffer);
           socket.flush();
           //读取信息
           qDebug("读取信息");
         if(socket.waitForReadyRead()){//在一定时间内是否有数据传入
              //先读长度 length
               QByteArray lengthBuffer=socket.readAll();
               QJsonObject dataLength=QJsonDocument::fromJson(lengthBuffer).object();
               int allLength =dataLength.value("length").toInt();
               //再按长度读传入数据 while  .append(socket)
               //发送确认信息
               qDebug()<<"length:"<<allLength;
               bool confirmFlag=true;
               QJsonObject confirm;
               confirm.insert("flag",confirmFlag);
               QByteArray confirmArray=QJsonDocument(confirm).toJson();
               socket.write(confirmArray);
               socket.flush();
               if(socket.waitForReadyRead()){
                   QByteArray dataBuffer=socket.readAll();
                   while(dataBuffer.length()<allLength){
                      dataBuffer.append(socket.readAll());
                  }
                 dataIn=QJsonDocument::fromJson(dataBuffer).array();
               }
                return true;
           }
           else {
               qDebug("出错");
                return false;
           }
    }else {
         qDebug("连接服务器失败");}

}
