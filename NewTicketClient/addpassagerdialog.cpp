#include "addpassagerdialog.h"
#include "ui_addpassagerdialog.h"
#include <QMessageBox>
AddPassagerDialog::AddPassagerDialog(User user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPassagerDialog)
{
    this->user=user;
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    regx1 = new QRegExp("[0-9]+$");
   QValidator *validator = new QRegExpValidator(*regx1, this );
    regx2 =new QRegExp("[0-9X]+$");
   QValidator *validator2 = new QRegExpValidator(*regx2, this );
   ui->lineEdit_phone->setValidator( validator );
   ui->lineEdit_cid->setValidator( validator2 );
}

AddPassagerDialog::~AddPassagerDialog()
{
     delete ui;
}

void AddPassagerDialog::on_buttonBox_accepted()
{
    QString name=ui->lineEdit_name->text();
    QString phone=ui->lineEdit_phone->text();
    QString cid=ui->lineEdit_cid->text();
    QString type;

    if(name==""){
        QMessageBox message(QMessageBox::NoIcon,"提示信息","未填写姓名");
        message.exec();
        return;
    }
    if(phone==""){
        QMessageBox message(QMessageBox::NoIcon,"提示信息","未填写手机号");
        message.exec();
        return;
    }
    if(cid==""){
        QMessageBox message(QMessageBox::NoIcon,"提示信息","未填写证件号");
        message.exec();
        return;
    }
    if(cid.length()!=18){
            QMessageBox message(QMessageBox::NoIcon, "身份证号输入错误", "请输入正确的身份证号.");
            message.exec();
            return;
        }
    if(ui->comboBox_type->currentIndex()==0){
        QMessageBox message(QMessageBox::NoIcon,"未选择乘客类型","请选择类型");
        message.exec();
        return;
    }else if(ui->comboBox_type->currentIndex()==1){
        type="成人";
    }else if(ui->comboBox_type->currentIndex()==2){
        type="学生";
    }



    //与服务器交互
    QJsonObject addJson;
    addJson.insert("request",4);
    addJson.insert("uid",user.getID());
    addJson.insert("name",name);
    addJson.insert("phone",phone);
    addJson.insert("cid",cid);
    addJson.insert("type",type);

    QJsonArray addBuffer;

    Client::GetInstance()->handleData(addJson,addBuffer);

    if(addBuffer.at(0).toBool()){
        QMessageBox message(QMessageBox::NoIcon,"添加信息","添加乘客成功");
        message.exec();

        //处理user 在第一个空处加信息
//        qDebug()<<"passagerNums1:"<<user.getPassagersNum();
//        for(int i=0;i<5;i++){
//            if(user.passagers[i].getCredentID()==NULL){
//                user.passagers[i].setName(name);
//                user.passagers[i].setphoneNumber(phone);
//                user.passagers[i].setCredentID(cid);
//                user.passagers[i].setType(type);
//                user.setPassagersNum(user.getPassagersNum()+1);
//                break;
//            }
//        }
//        qDebug()<<"passagerNums2:"<<user.getPassagersNum();
        this->close();
    }else{
        QMessageBox message(QMessageBox::NoIcon,"添加信息","添加乘客失败");
        message.exec();
    }

    //传回user到Ui
  //  emit getUser(user);
}

void AddPassagerDialog::on_buttonBox_rejected()
{
    //传回user到Ui
}
