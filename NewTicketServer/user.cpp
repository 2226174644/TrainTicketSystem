#include "user.h"

User::User()
{

}
void User::setName(QString name){
    userName=name;
}
QString User:: getName(){
    return userName;
}
void User:: setID(QString id){
    userId=id;
}

QString User:: getID(){
    return userId;
}
void User:: setPsw(QString psw){
    userPsw=psw;
}
QString User:: getPsw(){
    return userPsw;
}
void User:: setAmount(double money){
    amount=money;
}
double User:: getAmount(){
    return amount;
}
void User:: setLoginFlag(bool flag){
    loginFlag=flag;
}
bool User:: getLoginFlag(){
    return loginFlag;
}

void User::setPassagersNum(int num)
{
    passagersNum=num;
}

int User::getPassagersNum()
{
    return passagersNum;
}

void User::setType(QString userType)
{
    type=userType;
}

QString User::getType()
{
    return type;
}
void User::setphoneNumber(QString phone){
    phoneNumber=phone;
}
QString User::getphoneNumber(){
    return phoneNumber;
}
void User:: setSex(QString sex){
    userSex=sex;
}
QString User:: getSex(){
    return  userSex;
}
void User:: setCredentID(QString cId){
    credentId=cId;
}
QString User:: getCredentID(){
    return credentId;
}
