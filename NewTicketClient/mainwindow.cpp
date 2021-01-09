#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"


#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_login->setVisible(true);
    ui->groupBox__user->setVisible(false);
    //connect(regUi,SIGNAL(signalClose()),this,SLOT(onCloseDeleletRegUi()));


}

MainWindow::~MainWindow()
{
    delete ui;
    //delete ticketsUi;
}

//void MainWindow::onCloseDeleletRegUi()
//{
//    qDebug()<<"进入";
//    if(regUi != nullptr)
//       delete regUi;
//}


void MainWindow::on_loginButton_clicked()
{
    QString uid=ui->uid_lineEdit->text();
    QString psw=ui->psw_lineEdit->text();
    if(uid.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "用户名错误", "请输入用户名.");
        message.exec();
        return;
    }
    if(psw.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "密码错误", "请输入密码.");
        message.exec();
        return;
    }
    QJsonObject loginJson;
    loginJson.insert("request",1);
    loginJson.insert("uid",uid);
    loginJson.insert("psw",psw);
    //QByteArray loginArray=QJsonDocument(loginJson).toJson();

//    Client::GetInstance()->sendData(loginJson);
    QJsonArray confirmBuffer;
//    Client::GetInstance()->receiveData(confirmBuffer);
    Client::GetInstance()->handleData(loginJson,confirmBuffer);
    //Client::GetInstance()->handleData(loginJson,confirmBuffer);
    if(confirmBuffer.at(0).toBool()){
        QMessageBox message(QMessageBox::NoIcon, "登陆成功", "登陆成功.");
        message.exec();
        user.setLoginFlag(true);
        user.setID(uid);//1
        user.setPsw(psw);//2
        user.setName(confirmBuffer.at(3).toString());
        user.setAmount(confirmBuffer.at(4).toDouble());
        user.setphoneNumber(confirmBuffer.at(5).toString());
        user.setCredentID(confirmBuffer.at(6).toString());
        user.setSex(confirmBuffer.at(7).toString());
        user.setType(confirmBuffer.at(8).toString());

       //加载乘车人
        int passagersNum=confirmBuffer.size()-9;
        qDebug()<<"passagerNUm:"<<passagersNum;
        user.setPassagersNum(passagersNum);
        user.passagers=new User[5];

        for(int i=9;i<confirmBuffer.size();i++){
         QJsonObject temp;
         temp=confirmBuffer.at(i).toObject();
         user.passagers[i-9].setName(temp.value("name").toString());
         user.passagers[i-9].setCredentID(temp.value("cId").toString());
         user.passagers[i-9].setphoneNumber(temp.value("phone").toString());
         user.passagers[i-9].setType(temp.value("type").toString());

           }
    }else{
        QMessageBox message(QMessageBox::NoIcon, "登录失败", "登录失败.");
        message.exec();
        return;
    }
        ui->groupBox_login->setVisible(false);
        ui->groupBox__user->setVisible(true);
        ui->label_id->setText(user.getID());
        ui->label_name->setText(user.getName());
        ui->label_sex->setText(user.getSex());
}

void MainWindow::on_searchButton_clicked()
{
    QString fromPlace=ui->lineEdit_from->text();
    QString toPlace=ui->lineEdit_to->text();
    QDate dateline=ui->dateEdit->date();
    QString date=QString::number(dateline.year())+"-"+QString::number(dateline.month())+"-"+QString::number(dateline.day());
    qDebug()<<"date:"<<date<<endl;
    if(!user.getLoginFlag()){//未登录
        QMessageBox message(QMessageBox::NoIcon, "尚未登录", "请先登录再进行查询.");
        message.exec();
        return;
    }else if(fromPlace.isEmpty()||toPlace.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写地址", "请选择正确的出发地和目的地.");
        message.exec();
        return;
    }else if(date.isEmpty()){
        QMessageBox message(QMessageBox::NoIcon, "未填写时间", "请选择正确时间.");
        message.exec();
        return;
    }else{

        QJsonObject searchJson;
        searchJson.insert("request",5);
        searchJson.insert("from",fromPlace);
        searchJson.insert("to",toPlace);
        searchJson.insert("date",date);
        QJsonArray receiveTickets;

        Client::GetInstance()->handleData(searchJson,receiveTickets);
        if(receiveTickets.at(0).toBool()){
             ticketsUi=new TicketsUi(user,receiveTickets,fromPlace,toPlace,dateline);
             ticketsUi->setWindowTitle("车票查询");
             ticketsUi->show();

         }else{
            QMessageBox message(QMessageBox::NoIcon, "查询结果", "查询失败.");
            message.exec();
        }
    }
}
void MainWindow::on_pushButton_moreInfo_clicked()
{
    if(!user.getLoginFlag()){//未登录
        QMessageBox message(QMessageBox::NoIcon, "尚未登录", "请先登录再进行查询.");
        message.exec();
        return;
    }else{
        userUi=new UserUI(user);
        userUi->setWindowTitle("用户中心");
        userUi->show();
    }
}

void MainWindow::on_pushButton_register_clicked()
{
        regUi=new registerUi();
        regUi->setWindowTitle("注册");
        regUi->show();

}

void MainWindow::on_pushButton_exit_clicked()
{
    ui->groupBox__user->setVisible(false);
    ui->groupBox_login->setVisible(true);
    user.setLoginFlag(false);
    ui->uid_lineEdit->setText("");
    ui->psw_lineEdit->setText("");
    QMessageBox message(QMessageBox::NoIcon, "退出成功", "退出用户成功.");
    message.exec();
}
