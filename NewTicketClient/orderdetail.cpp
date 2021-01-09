#include "client.h"
#include "orderdetail.h"
#include "ui_orderdetail.h"

#include <QJsonArray>
#include <QMessageBox>
#include <QPushButton>

OrderDetail::OrderDetail(User user,QJsonObject orderObject,QString orderId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderDetail)
{
    ui->setupUi(this);

    this->orderId=orderId;

//    trainId=orderObject.value("trainId").toString();
//    fromStation=orderObject.value("fromStation").toString();
//    toStation=orderObject.value("toStation").toString();
//    QString startTime=orderObject.value("startTime").toString();
//    QString arriveTime=orderObject.value("arriveTime").toString();
     orderStatus=orderObject.value("status").toString();
     QString orderDate=orderObject.value("date").toString();
//    double price=orderObject.value("price").toDouble();

//    ui->label_from->setText(fromStation);
//    ui->label_to->setText(toStation);
//    ui->label_startTime->setText(startTime);
//    ui->label_arriveTime->setText(arriveTime);
//    ui->label_trainId->setText(trainId);

    ui->label_status->setText("订单状态："+orderStatus);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("支付"));

    //表格
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(15);

    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,180);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,150);
    ui->tableWidget->setColumnWidth(7,70);
    ui->tableWidget->setColumnWidth(8,70);
    ui->tableWidget->setColumnWidth(9,50);
    ui->tableWidget->setColumnWidth(10,50);
    ui->tableWidget->setColumnWidth(11,100);
    ui->tableWidget->setColumnWidth(12,80);
    ui->tableWidget->setColumnWidth(13,50);
    ui->tableWidget->setColumnWidth(14,50);

    QStringList header;
            header.append(QObject::tr("姓名"));
            header.append(QObject::tr("证件号"));
            header.append(QObject::tr("车次"));
            header.append(QObject::tr("车型"));
            header.append(QObject::tr("出发地点-到底地点"));
            header.append(QObject::tr("日期"));
            header.append(QObject::tr("出发时间-到达时间"));
            header.append(QObject::tr("席次"));
            header.append(QObject::tr("票种"));
            header.append(QObject::tr("车厢"));
            header.append(QObject::tr("座位号"));
            header.append(QObject::tr("金额"));
            header.append(QObject::tr("状态"));
            header.append(QObject::tr("退票"));
            header.append(QObject::tr("改签"));
    ui->tableWidget->setHorizontalHeaderLabels(header);

    init();
}

OrderDetail::~OrderDetail()
{
    delete ui;
}

void OrderDetail::init()
{
    ui->tableWidget->clearContents();
    QJsonObject more;
    more.insert("request",10);
    more.insert("orderId",orderId);

    Client::GetInstance()->handleData(more,detailArray);
//    if(!detailArray.at(0).isBool()){
//        QMessageBox message(QMessageBox::NoIcon,"提示", "加载失败.");
//        message.exec();
//        this->close();
//    }
    status=new int[detailArray.size()];
    for(int i=0;i<detailArray.size();i++){
        status[i]=0;
    }
    double price=0.0;
    ui->tableWidget->setRowCount(detailArray.size());
    int cancelNum=0;
    for (int i=0;i<detailArray.size();i++) {
           QJsonObject temp=detailArray.at(i).toObject();
           QString name=temp.value("name").toString();
           QString cid=temp.value("cid").toString();
           QString passagerType=temp.value("passagerType").toString();
           int coach=temp.value("coach").toInt();
           QString seat=temp.value("seat").toString();
           double soloPrice=temp.value("price").toDouble();
           QString chairType;
           QString ticketStatus=temp.value("ticketStatus").toString();
           QString trainId=temp.value("trainId").toString();
           QString fromStation=temp.value("fromStation").toString();
           QString toStation=temp.value("toStation").toString();
           QString startTime=temp.value("startTime").toString();
           QString arriveTime=temp.value("arriveTime").toString();
           QString ticketDate=temp.value("ticketDate").toString();
           QString trainType=temp.value("trainType").toString();



           if(ticketStatus=="已退票"){
               status[i]=1;
               cancelNum++;
           }else{
               price+=soloPrice;
           }

           if(coach>=4){
               chairType="二等座";
           }
           else if(coach>1&&coach<4){
               chairType="一等座";
           }
           else if(coach==1){
               chairType="商务座";
           }
           ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
           ui->tableWidget->setItem(i,1,new QTableWidgetItem(cid));
           ui->tableWidget->setItem(i,2,new QTableWidgetItem(trainId));
           ui->tableWidget->setItem(i,3,new QTableWidgetItem(trainType));
           ui->tableWidget->setItem(i,4,new QTableWidgetItem(fromStation+"-"+toStation));
           ui->tableWidget->setItem(i,5,new QTableWidgetItem(ticketDate));
           ui->tableWidget->setItem(i,6,new QTableWidgetItem(startTime+"-"+arriveTime));
           ui->tableWidget->setItem(i,7,new QTableWidgetItem(chairType));
           ui->tableWidget->setItem(i,8,new QTableWidgetItem(passagerType));
           ui->tableWidget->setItem(i,9,new QTableWidgetItem(QString::number(coach)));
           ui->tableWidget->setItem(i,10,new QTableWidgetItem(seat));
           ui->tableWidget->setItem(i,11,new QTableWidgetItem("￥ "+QString::number(soloPrice)));
           ui->tableWidget->setItem(i,12,new QTableWidgetItem(ticketStatus));



           QPushButton* cancelBtn = new QPushButton;
           cancelBtn->setText("退票");
           ui->tableWidget->setCellWidget(i,13,cancelBtn);
           connect(cancelBtn,SIGNAL(clicked()),this,SLOT(cancelOrder()));


           QPushButton* switchBtn = new QPushButton;
           switchBtn->setText("改签");
           ui->tableWidget->setCellWidget(i,14,switchBtn);
           connect(switchBtn,SIGNAL(clicked()),this,SLOT(switchOrder()));

//           if(ticketStatus=="已退票"){
//               ui->tableWidget->item(i,8)->setFlags(Qt::ItemIsEnabled);
//               ui->tableWidget->item(i,9)->setFlags(Qt::ItemIsEnabled);
//           }
    }
    if(cancelNum==detailArray.size()) orderStatus="已失效";
    ui->label_status->setText("订单状态："+orderStatus);
    ui->label_total->setText("合计：￥"+QString::number(price));
}

void OrderDetail::cancelOrder()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
            return;
        int x = pushBtn->frameGeometry().x();
        int y = pushBtn->frameGeometry().y();
        QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
        int row = index.row();
        int colum = index.column();
        qDebug() << QObject::tr("cancel row, row: %1, colum: %2").arg(row).arg(colum);

        if(row>=0){
            if(status[row]!=1){
            QJsonObject temp=detailArray.at(row).toObject();

            temp.insert("request",11);
            temp.insert("orderId",orderId);
            temp.insert("flag",0);

            QJsonArray cancelArray;
            Client::GetInstance()->handleData(temp,cancelArray);
            if(cancelArray.at(0).isBool()){
                QMessageBox message(QMessageBox::NoIcon, "退票信息", "退票成功.");
                message.exec();
                //ui->tableWidget->setItem(row,12,new QTableWidgetItem("已退票"));
                init();
                status[row]=1;

            }else{
                QMessageBox message(QMessageBox::NoIcon, "退票信息", "退票失败.");
                message.exec();
            }
            }else{
                QMessageBox message(QMessageBox::NoIcon, "提示信息", "已退票则无法进行此操作.");
                message.exec();
            }

        }
}

void OrderDetail::switchOrder()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
            return;
        int x = pushBtn->frameGeometry().x();
        int y = pushBtn->frameGeometry().y();
        QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
        int row = index.row();
        int colum = index.column();
        qDebug() << QObject::tr("Switch row, row: %1, colum: %2").arg(row).arg(colum);
        if(row>=0){
            if(status[row]!=1){
                QJsonObject temp=detailArray.at(row).toObject();
                QJsonObject searchJson;
                searchJson.insert("request",5);
                searchJson.insert("from",temp.value("fromStation").toString());
                searchJson.insert("to",temp.value("toStation").toString());
                searchJson.insert("date",temp.value("ticketDate").toString());
                QJsonArray receiveTickets;

                Client::GetInstance()->handleData(searchJson,receiveTickets);
                if(receiveTickets.at(0).toBool()){
                     switchDialog=new SwitchOrderDialog(orderId,temp,receiveTickets);
                     switchDialog->setWindowTitle("改签");
                     switchDialog->exec();
                     init();
                 }else{
                    QMessageBox message(QMessageBox::NoIcon, "查询结果", "查询失败.");
                    message.exec();
                }

            }else{
                QMessageBox message(QMessageBox::NoIcon, "提示信息", "已退票则无法进行此操作.");
                message.exec();
            }
        }
}

void OrderDetail::on_buttonBox_accepted()
{
    if(orderStatus!="已失效"){
    QJsonObject payJson;
    payJson.insert("request",14);
    payJson.insert("orderId",orderId);
    QJsonArray returnPay;
    Client::GetInstance()->handleData(payJson,returnPay);
    if(returnPay.at(0).isBool()){
        QMessageBox message(QMessageBox::NoIcon, "提示信息", "支付成功.");
        message.exec();
    }else{
        QMessageBox message(QMessageBox::NoIcon, "提示信息", "支付失败.");
        message.exec();
    }
    }else{
        QMessageBox message(QMessageBox::NoIcon, "提示信息", "订单已失效，无法再支付.");
        message.exec();
    }
}
