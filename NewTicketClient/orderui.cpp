#include "orderui.h"
#include "ui_orderui.h"
#include "QJsonObject"
#include "QJsonArray"
#include "client.h"

#include <QPushButton>

OrderUi::OrderUi(User user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderUi)
{
    this->user=user;
    ui->setupUi(this);

    init();

}

OrderUi::~OrderUi()
{
    delete ui;
}

void OrderUi::init()
{
    ui->tableWidget->clearContents();
    QJsonObject searchOrder;
    searchOrder.insert("request",9);
    searchOrder.insert("uid",user.getID());

    Client::GetInstance()->handleData(searchOrder,orderArray);

    order=new QString[orderArray.size()];
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(orderArray.size());
    ui->tableWidget->setColumnWidth(0,150);
//    ui->tableWidget->setColumnWidth(1,50);
//    ui->tableWidget->setColumnWidth(2,125);
    ui->tableWidget->setColumnWidth(1,180);
//    ui->tableWidget->setColumnWidth(4,125);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,50);
    QStringList header;
            header.append(QObject::tr("订单号"));
//            header.append(QObject::tr("车次"));
//            header.append(QObject::tr("出发站-到达站"));
            header.append(QObject::tr("订单日期"));
//            header.append(QObject::tr("出发时间-到达时间"));
            header.append(QObject::tr("状态"));
            header.append(QObject::tr("金额"));
            header.append(QObject::tr("详情"));
    ui->tableWidget->setHorizontalHeaderLabels(header);

    for(int i=0;i<orderArray.size();i++){
        QJsonObject temp=orderArray.at(i).toObject();
        QString orderId=temp.value("orderId").toString();
        order[i]=orderId;
        QString trainId=temp.value("trainId").toString();
//        QString fromStation=temp.value("fromStation").toString();
//        QString toStation=temp.value("toStation").toString();
//        QString startTime=temp.value("startTime").toString();
//        QString arriveTime=temp.value("arriveTime").toString();
        QString status=temp.value("status").toString();
//        QString ticketDate=temp.value("date").toString();
        QString orderDate=temp.value("orderDate").toString();
        double price=temp.value("price").toDouble();

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(orderId));
//        ui->tableWidget->setItem(i,1,new QTableWidgetItem(trainId));
//        ui->tableWidget->setItem(i,2,new QTableWidgetItem(fromStation+"-"+toStation));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(orderDate));
//        ui->tableWidget->setItem(i,4,new QTableWidgetItem(startTime+"-"+arriveTime));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(status));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem("￥ "+QString::number(price)));

        QPushButton* btn = new QPushButton;
        btn->setText("详情");
        ui->tableWidget->setCellWidget(i,4,btn);
        connect(btn,SIGNAL(clicked()),this,SLOT(detailThisRow()));
    }
}

void OrderUi::detailThisRow()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
            return;
        int x = pushBtn->frameGeometry().x();
        int y = pushBtn->frameGeometry().y();
        QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
        int row = index.row();
        int colum = index.column();
        qDebug() << QObject::tr("Remove row, row: %1, colum: %2").arg(row).arg(colum);

        if(row>=0){
            QJsonObject orderObject=orderArray.at(row).toObject();
            orderDetail=new OrderDetail(user,orderObject,order[row]);
            orderDetail->setWindowTitle("订单详情");
            orderDetail->exec();
            init();
        }
}
