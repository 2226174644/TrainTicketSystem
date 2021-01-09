#ifndef SERVICE_H
#define SERVICE_H
#include "QJsonArray"
#include "QJsonObject"
#include "QJsonDocument"
#include "QSqlDatabase"
#include "QSqlDriver"

class service
{
public:
    enum operation{DEBUG=0,LOGIN,REGISTER,DELETEPASSAGER,ADDPASSAGER,SEARCHTICKETS,ORDER,ORDERPASSAGER,UPDATEUSER,SEARCHORDER,ORDERDETAIL,CANCELORDER,SWITCHORDER,TRANSFER,PAYORDER };
    ~service();

    static service* getInstance();
    void handleRqst(QJsonObject& inJson, QJsonArray& outJsonArray);

private:
    service();
    static service* serv;
    QSqlDatabase db;

    void debug(QJsonObject& inJson, QJsonArray& outJsonArray);
    void error(QJsonObject& inJson, QJsonArray& outJsonArray);
    void login(QJsonObject& inJson, QJsonArray& outJsonArray);
    void logout(QJsonObject& inJson, QJsonArray& outJsonArray);
    void Register(QJsonObject& inJson, QJsonArray& outJsonArray);
    void deletePassager(QJsonObject& inJson, QJsonArray& outJsonArray);
    void addPassager(QJsonObject& inJson, QJsonArray& outJsonArray);
    void searchTickets(QJsonObject& inJson, QJsonArray& outJsonArray);
    void createOrder(QJsonObject& inJson, QJsonArray& outJsonArray);
    void addOrderPassager(QJsonObject& inJson, QJsonArray& outJsonArray);
    void updateUser(QJsonObject& inJson, QJsonArray& outJsonArray);
    void searchOrder(QJsonObject& inJson, QJsonArray& outJsonArray);
    void orderDetail(QJsonObject& inJson, QJsonArray& outJsonArray);
    void cancelOrder(QJsonObject& inJson, QJsonArray& outJsonArray);
    void switchOrder(QJsonObject& inJson, QJsonArray& outJsonArray);
    void transfer(QJsonObject& inJson, QJsonArray& outJsonArray);
    void payOrder(QJsonObject& inJson, QJsonArray& outJsonArray);
};

#endif // SERVICE_H
