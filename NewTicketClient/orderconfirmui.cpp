#include "orderconfirmui.h"
#include "ui_orderconfirmui.h"

#include <QDateTime>
#include <qmessagebox.h>

OrderConfirmUi::OrderConfirmUi(User user, Tickets ticket, QComboBox passagerTypes[], QComboBox chairTypes[], int status[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderConfirmUi)
{
    this->user=user;
    this->status=status;
    this->ticket=ticket;
    this->chairType=chairTypes;
    this->passagerType=passagerTypes;
    ui->setupUi(this);

    for(int i=0;i<6;i++){
        price[i]=0.0;
    }

    int people=0;
    for(int i=0;i<6;i++){
        if(status[i]==1){
            people++;
        }
    }

    QString info=ticket.getDate()+ " " +ticket.getTrainId()+"次 " +ticket.getFromPlace()+"站 （"+ ticket.getStartTime()+"开） ——"+ticket.getToPlace()+"站 ("+ ticket.getArriveTime()+" 到）";
    ui->ticketInfoLabel->setText(info);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(people);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,180);
    ui->tableWidget->setColumnWidth(4,110);
    ui->tableWidget->setColumnWidth(5,80);
    QStringList header;
    header.append(QObject::tr("票种"));
    header.append(QObject::tr("席别"));
    header.append(QObject::tr("姓名"));
    header.append(QObject::tr("证件号"));
    header.append(QObject::tr("手机号"));
    header.append(QObject::tr("价格"));
    ui->tableWidget->setHorizontalHeaderLabels(header);


    int row=0;
    //表格user
    if(status[0]==1){
        //        int row=ui->tableWidget->currentRow();
        //        ui->tableWidget->setRowCount(row+1);

        ui->tableWidget->setItem(row,0,new QTableWidgetItem(passagerTypes[0].currentText()));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(chairTypes[0].currentText()));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(user.getName()));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(user.getCredentID()));
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(user.getphoneNumber()));

        //价格
        if (chairTypes[0].currentText()=="二等座") {
            num0++;
            if(passagerTypes[0].currentIndex()==0){
                ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(ticket.getTicketsPay2())));
                price[0]=ticket.getTicketsPay2();
            }else{
                ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay2()*0.75))));
                price[0]=ticket.getTicketsPay2()*0.75;
            }
        }else if(chairTypes[0].currentText()=="一等座"){
            num1++;
            if(passagerTypes[0].currentIndex()==0){
                ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay1()))));
                price[0]=ticket.getTicketsPay1();
            }else{
                ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay1()*0.75))));
                price[0]=ticket.getTicketsPay1()*0.75;
            }
           }else if(chairTypes[0].currentText()=="商务座"){
            num2++;
            if(passagerTypes[0].currentIndex()==0){
                ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay0()))));
                price[0]=ticket.getTicketsPay0();
            }else{
                ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay0()*0.75))));
                price[0]=ticket.getTicketsPay0()*0.75;
            }

        }
        row++;
    }

    //乘客
    for(int i=0;i<5;i++){
        if(status[i+1]==1){
            //            int row=ui->tableWidget->currentRow();
            //            ui->tableWidget->setRowCount(row+1);

            ui->tableWidget->setItem(row,0,new QTableWidgetItem(passagerTypes[i+1].currentText()));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(chairTypes[i+1].currentText()));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(user.passagers[i].getName()));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(user.passagers[i].getCredentID()));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(user.passagers[i].getphoneNumber()));

            if(chairTypes[i+1].currentText()=="二等座") {
                num0++;
                if(passagerTypes[i+1].currentIndex()==0){
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay2()))));
                    price[i+1]=ticket.getTicketsPay2();
                }else{
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay2()*0.75))));
                    price[i+1]=ticket.getTicketsPay2()*0.75;
                }
              }else if(chairTypes[i+1].currentText()=="一等座"){
                num1++;
                if(passagerTypes[i+1].currentIndex()==0){
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay1()))));
                    price[i+1]=ticket.getTicketsPay1();
                }else{
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay1()*0.75))));
                    price[i+1]=ticket.getTicketsPay1()*0.75;
                }
            }else if(chairTypes[i+1].currentText()=="商务座"){
                num2++;
                if(passagerTypes[i+1].currentIndex()==0){
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay0()))));
                    price[i+1]=ticket.getTicketsPay0();
                }else{
                    ui->tableWidget->setItem(row,5,new QTableWidgetItem((QString::number(ticket.getTicketsPay0()*0.75))));
                    price[i+1]=ticket.getTicketsPay0()*0.75;
                }

            }
            row++;
        }
    }
    //合计
    for(int i=0;i<6;i++){
        sum+=price[i];
    }
    ui->priceLabel->setText("合计："+QString::number(sum)+"元");
}
OrderConfirmUi::~OrderConfirmUi()
{
    delete ui;
}

void OrderConfirmUi::on_buttonBox_accepted()
{
    QString orderId;
    if(ticket.orderId==""){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss:zz");
    QJsonObject orderJson;
    orderJson.insert("request",6);
    orderJson.insert("uid",user.getID());
    orderJson.insert("time",current_date);
    orderJson.insert("price",sum);

    QJsonArray orderCheck;

    //整体订单
    Client::GetInstance()->handleData(orderJson,orderCheck);
    if(orderCheck.at(0).toBool()){
        orderId=orderCheck.at(1).toString();
    }else{
        QMessageBox message(QMessageBox::NoIcon, "提交失败", "订单提交失败.");
        message.exec();
        return;
    }
    }else{
        orderId=ticket.orderId;
    }


    //公共属性
//    tempArray.append(orderId);
//    tempArray.append(ticket.getTrainId());
//    tempArray.append(ticket.getFromPlace());
//    tempArray.append(ticket.getToPlace());

    QJsonObject orderPassager;
    orderPassager.insert("request",7);
    orderPassager.insert("orderId",orderId);
    orderPassager.insert("trainId",ticket.getTrainId());
    orderPassager.insert("fromStation",ticket.getFromPlace());
    orderPassager.insert("toStation",ticket.getToPlace());
    orderPassager.insert("date",ticket.getDate());

    QJsonArray tempArray;
    //乘客订单
    for(int i=0;i<6;i++){
        if(status[i]==1){
            //        QJsonObject temp;
            //        temp.insert("request",7);
            //        temp.insert("orderId",orderId);
            //        temp.insert("tid",ticket.getTrainId());
            //        temp.insert("from",ticket.getFromPlace());
            //        temp.insert("to",ticket.getToPlace());
            //        temp.insert("chairType",chairType[i].currentText());
            //        temp.insert("passagerType",passagerType[i].currentText());
            //        temp.insert("price",price[i]);

            //信息放入jsonarray

            if(i==0){
                //            temp.insert("name",user.getName());
                //            temp.insert("cid",user.getCredentID());
                tempArray.append(user.getName());
                tempArray.append(user.getCredentID());

            }else{
                //            temp.insert("name",user.passagers[i-1].getName());
                //            temp.insert("cid",user.passagers[i-1].getName());
                tempArray.append(user.passagers[i-1].getName());
                tempArray.append(user.passagers[i-1].getCredentID());
            }
            tempArray.append(chairType[i].currentText());
            tempArray.append(passagerType[i].currentText());
            tempArray.append(price[i]);
        }
    }
    orderPassager.insert("info",tempArray);
    orderPassager.insert("num0",num0);
    orderPassager.insert("num1",num1);
    orderPassager.insert("num2",num2);
    QJsonArray check;
    Client::GetInstance()->handleData(orderPassager,check);
    if(check.at(0).isBool()){
        QMessageBox message(QMessageBox::NoIcon, "订单提交成功", "请前往个人中心完成支付订单.");
        message.exec();
    }else{
        QMessageBox message(QMessageBox::NoIcon, "订单提交失败", "订单提交失败");
        message.exec();
        return;
    }

    //关闭的同时关闭父界面
   emit confirmButton(orderId);
}
