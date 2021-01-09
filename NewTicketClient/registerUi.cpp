#include "registerUi.h"
#include "ui_registerUi.h"

#include <QMessageBox>

registerUi::registerUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registerUi)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
     regx1 = new QRegExp("[0-9]+$");
    QValidator *validator = new QRegExpValidator(*regx1, this );
     regx2 =new QRegExp("[0-9X]+$");
    QValidator *validator2 = new QRegExpValidator(*regx2, this );
    ui->lineEdit_phoneNumber->setValidator( validator );
    ui->lineEdit_credentID->setValidator( validator2 );
}

registerUi::~registerUi()
{
    delete regx1,regx2;
    delete ui;
}

void registerUi::closeEvent(QCloseEvent *event)
{
    //emit signalClose();
}
void registerUi::on_enterButton_clicked()
{
    QString name=ui->lineEdit_name->text();
    QString uid=ui->lineEdit_id->text();
    QString psw=ui->lineEdit_password->text().trimmed();
    QString psw2=ui->lineEdit_confirmPassword->text().trimmed();
    QString phoneNumber=ui->lineEdit_phoneNumber->text().trimmed();
    QString credentId=ui->lineEdit_credentID->text().trimmed();
    QString sex;
    QString type;

    //处理姓名
    if(name.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写姓名", "请填写姓名.");
        message.exec();
        return;
    }
    //处理uid
    if(uid.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写ID", "请填写ID.");
        message.exec();
        return;
    }
    //处理密码
    if(psw.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写密码", "请填写密码.");
        message.exec();
        return;
    }
    if(psw2.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写密码", "请填写密码.");
        message.exec();
        return;
    }else if (QString::compare(psw,psw2)!=0){
        QMessageBox message(QMessageBox::NoIcon, "前后密码不一致", "请重新输入密码.");
        message.exec();
        return;
    }
    //处理手机号
    if(phoneNumber.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写手机号", "请输入手机号.");
        message.exec();
        return;
    }else if(phoneNumber.length()!=11){
        QMessageBox message(QMessageBox::NoIcon, "手机号输入错误", "请输入正确的手机号.");
        message.exec();
        return;
    }
    //处理身份证号
    if(credentId.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写身份证号", "请输入身份证号.");
        message.exec();
        return;
    }else if(credentId.length()!=18){
        QMessageBox message(QMessageBox::NoIcon, "身份证号输入错误", "请输入正确的身份证号.");
        message.exec();
        return;
    }
    //处理性别
    if(ui->sexComboBox->currentIndex()==0){
        QMessageBox message(QMessageBox::NoIcon, "未选择性别", "请选择性别.");
        message.exec();
        return;
    }else if(ui->sexComboBox->currentIndex()==1){
        sex="男";
    }else if (ui->sexComboBox->currentIndex()==2) {
        sex="女";
    }
    //处理类型
    if(ui->typeComboBox->currentIndex()==0){
        QMessageBox message(QMessageBox::NoIcon, "未选择类型", "请选择类型.");
        message.exec();
        return;
    }else if(ui->typeComboBox->currentIndex()==1){
        type="成人";
    }else if (ui->typeComboBox->currentIndex()==2) {
        type="学生";
    }
    QJsonObject registerJson;
    registerJson.insert("request",2);
    registerJson.insert("name",name);
    registerJson.insert("uid",uid);
    registerJson.insert("password",psw);
    registerJson.insert("phoneNumber",phoneNumber);
    registerJson.insert("credentId",credentId);
    registerJson.insert("sex",sex);
    registerJson.insert("type",type);
//    registerJson.insert("passagerNum",0);
//    Client::GetInstance()->sendData(registerJson);
    QJsonArray registerBuffer;
//    Client::GetInstance()->receiveData(registerBuffer);
    Client::GetInstance()->handleData(registerJson,registerBuffer);
    if(registerBuffer.at(0).toBool()){
        QMessageBox message(QMessageBox::NoIcon, "注册信息", "注册成功！.");
        message.exec();
        this->close();

    }else{
        QMessageBox message(QMessageBox::NoIcon, "注册信息", "注册失败！.");
        message.exec();

    }


}
