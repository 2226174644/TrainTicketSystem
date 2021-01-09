#ifndef USER_H
#define USER_H

#include <QString>



class User
{
private:
   QString userName;
   QString userId;
   QString userPsw;
   double amount=0;
   QString phoneNumber;
   QString credentId;
   QString userSex;
   QString type;
   bool loginFlag=false;
   int passagersNum;
public:
    User();
    void setName(QString name);
    QString getName();
    void setID(QString id);
    QString getID();
    void setPsw(QString psw);
    QString getPsw();
    void setAmount(double money);
    double getAmount();
    void setphoneNumber(QString phone);
    QString getphoneNumber();
    void setCredentID(QString cId);
    QString  getCredentID();
    void setSex(QString sex);
    QString getSex();
    void setLoginFlag(bool flag);
    bool getLoginFlag();
    void setPassagersNum(int num);
    int getPassagersNum();
    void setType(QString userType);
    QString getType();

    User *passagers;
};

#endif // USER_H
