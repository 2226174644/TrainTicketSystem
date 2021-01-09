#include "client.h"
#include "switchorderdialog.h"
#include "ui_switchorderdialog.h"

#include <qmessagebox.h>

SwitchOrderDialog::SwitchOrderDialog(QString orderId, QJsonObject orderObject,QJsonArray ticketArray, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SwitchOrderDialog)
{
    ui->setupUi(this);
    this->ticketsArray=ticketArray;
    this->orderId=orderId;
    this->tempOrder=orderObject;
    //comboBox
    if(orderObject.value("passagerType").toString()=="学生票"){
        ui->passagerComboBox->addItem(QObject::tr("成人票"));
        ui->passagerComboBox->addItem(QObject::tr("学生票"));
    }
    else{
        ui->passagerComboBox->addItem(QObject::tr("成人票"));
    }
    ui->passagerComboBox->setEnabled(true);

    //初始化表
    ui->ticketsTable->setWindowTitle("车次列表");
    ui->ticketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ticketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ticketsTable->setColumnCount(8);
    ui->ticketsTable->setRowCount(ticketsArray.size()-1);
    //设置列宽
    ui->ticketsTable->setColumnWidth(0,100);
    ui->ticketsTable->setColumnWidth(1,150);
    ui->ticketsTable->setColumnWidth(2,150);
    ui->ticketsTable->setColumnWidth(3,75);
    ui->ticketsTable->setColumnWidth(4,150);
    ui->ticketsTable->setColumnWidth(5,150);
    ui->ticketsTable->setColumnWidth(6,150);
    ui->ticketsTable->setColumnWidth(7,75);
    //设置行
    ui->ticketsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //设置表头
    QStringList header;
    header.append(QObject::tr("车次"));
    header.append(QObject::tr("出发站-到达站"));
    header.append(QObject::tr("出发时间-到达时间"));
    header.append(QObject::tr("历时"));
    header.append(QObject::tr("商务座"));
    header.append(QObject::tr("一等座"));
    header.append(QObject::tr("二等座"));
    header.append(QObject::tr("备注"));
    ui->ticketsTable->setHorizontalHeaderLabels(header);

    //初始化数据
    init();
}

SwitchOrderDialog::~SwitchOrderDialog()
{
    delete ui;
}

void SwitchOrderDialog::init()
{
    ui->ticketsTable->clearContents();
    ui->ticketsTable->setRowCount(ticketsArray.size()-1);
    tickets=new Tickets[ticketsArray.size()-1];


    for(int i=1;i<ticketsArray.size();i++){
        QJsonObject temp;
        temp=ticketsArray.at(i).toObject();
        tickets[i-1].setTrainId(temp.value("tId").toString());
        tickets[i-1].setFromPlace(temp.value("from").toString());
        tickets[i-1].setToPlace(temp.value("to").toString());
        tickets[i-1].setStartTime(temp.value("startTime").toString());
        tickets[i-1].setArriveTime(temp.value("arriveTime").toString());
        tickets[i-1].setTicketsNum0(temp.value("ticketsNum0").toInt());
        tickets[i-1].setTicketsNum1(temp.value("ticketsNum1").toInt());
        tickets[i-1].setTicketsNum2(temp.value("ticketsNum2").toInt());
//        tickets[i].setTicketsPay0(temp.value("ticketsPay0").toDouble());
//        tickets[i].setTicketsPay1(temp.value("ticketsPay1").toDouble());
//        tickets[i].setTicketsPay2(temp.value("ticketsPay2").toDouble());
    }
    //buttons =new QPushButton[ticketsArray.size()];

//    int iRow=ui->ticketsTable->rowCount();
//    ui->ticketsTable->setRowCount(iRow+1);


    for(int i=0;i<ticketsArray.size()-1;i++){

        QString tempstr = tickets[i].getTrainId();
        //车次
        ui->ticketsTable->setItem(i,0,new QTableWidgetItem(tempstr));

        //始发地-目的地
        QString from=tickets[i].getFromPlace();
        QString to=tickets[i].getToPlace();
        QString from_to=from+"-"+to;
        ui->ticketsTable->setItem(i,1,new QTableWidgetItem(from_to));

        //出发时间-到达时间
        QString start_arrive=tickets[i].getStartTime()+"-"+tickets[i].getArriveTime();
        ui->ticketsTable->setItem(i,2,new QTableWidgetItem(start_arrive));

        //历时
        QDateTime time1=QDateTime::fromString(tickets[i].getStartTime(),"hh:mm:ss");
        QDateTime time2=QDateTime::fromString(tickets[i].getArriveTime(),"hh:mm:ss");
        int secs=time1.secsTo(time2);
        int h=secs/3600;
        int m=(secs%3600)/60;
        QString time=QString::number(h)+" h "+QString::number(m)+" m ";
        ui->ticketsTable->setItem(i,3,new QTableWidgetItem(time));

        double price=(h*60+m)*1.5;
        tickets[i].setTicketsPay2(price);
        tickets[i].setTicketsPay1(price*1.5);
        tickets[i].setTicketsPay0(price*3);

        //商务座，一等座，二等座
        //座位不够时处理？？？
        ui->ticketsTable->setItem(i,4,new QTableWidgetItem("(￥"+QString::number(tickets[i].getTicketsPay0())+") "+QString::number(tickets[i].getTicektsNum0())+"张"));
        ui->ticketsTable->setItem(i,5,new QTableWidgetItem("(￥"+QString::number(tickets[i].getTicketsPay1())+") "+QString::number(tickets[i].getTicektsNum1())+"张"));
        ui->ticketsTable->setItem(i,6,new QTableWidgetItem("(￥"+QString::number(tickets[i].getTicketsPay2())+") "+QString::number(tickets[i].getTicketsNum2())+"张"));

        //购票按钮
        QPushButton *button =new QPushButton();
        button->setText(tr("改签"));
        button->setEnabled(true);
        ui->ticketsTable->setCellWidget(i,7,button);
        connect(button,SIGNAL(clicked()),this,SLOT(switchTicket()));
    }
}



void SwitchOrderDialog::switchTicket()
{
       //退票+买票
    QString passagerType=ui->passagerComboBox->currentText();
    QString chairType=ui->chairComboBox->currentText();
    double price=0;

    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
            return;
        int x = pushBtn->frameGeometry().x();
        int y = pushBtn->frameGeometry().y();
        QModelIndex index = ui->ticketsTable->indexAt(QPoint(x, y));
        int row = index.row();
        int colum = index.column();
        qDebug() << QObject::tr("Remove row, row: %1, colum: %2").arg(row).arg(colum);

        //价格
        switch (ui->chairComboBox->currentIndex()) {
        case 0:
            if(ui->passagerComboBox->currentIndex()==0){
                price=tickets[row].getTicketsPay2();
            }else{

                price=tickets[row].getTicketsPay2()*0.75;
            }
            break;
        case 1:
            if(ui->passagerComboBox->currentIndex()==0){
                price=tickets[row].getTicketsPay1();
            }else{
                price=tickets[row].getTicketsPay1()*0.75;
            }
            break;
        case 2:
            if(ui->passagerComboBox->currentIndex()==0){
                price=tickets[row].getTicketsPay0();
            }else{
                price=tickets[row].getTicketsPay0()*0.75;
            }
            break;
        }

        if(row>=0){
            if(tempOrder.value("trainId").toString()==tickets[row].getTrainId()){
                QMessageBox message(QMessageBox::NoIcon, "改签信息", "不能改签同一量车.");
                message.exec();
                return;
            }else{
            tempOrder.insert("request",11);
            tempOrder.insert("orderId",orderId);
            tempOrder.insert("flag",1);

            QJsonArray cancelArray;
            //退票
            Client::GetInstance()->handleData(tempOrder,cancelArray);
            if(cancelArray.at(0).isBool()){
               //买票
                tempOrder.insert("request",12);
                QJsonArray ticketTemp;
                ticketTemp.append(tickets[row].getTrainId());
                ticketTemp.append(tickets[row].getFromPlace());
                ticketTemp.append(tickets[row].getToPlace());

                QDate dateline=ui->dateEdit_2->date();
                QString date=QString::number(dateline.year())+"-"+QString::number(dateline.month())+"-"+QString::number(dateline.day());
                ticketTemp.append(date);
                ticketTemp.append(passagerType);
                ticketTemp.append(chairType);
                ticketTemp.append(price);

                tempOrder.insert("ticketInfo",ticketTemp);

                QJsonArray returnArray;
                Client::GetInstance()->handleData(tempOrder,returnArray);

                if(returnArray.at(0).isBool()){
                    QMessageBox message(QMessageBox::NoIcon, "改签信息", "改签成功.");
                    message.exec();
                    this->close();
                }else{
                    QMessageBox message(QMessageBox::NoIcon, "改签信息", "改签买票失败.");
                    message.exec();
                }

            }else{
                QMessageBox message(QMessageBox::NoIcon, "改签信息", "改签退票失败.");
                message.exec();
            }
        }
        }
}

void SwitchOrderDialog::on_pushButton_search_2_clicked()
{
    QString fromPlace=ui->lineEdit_from_2->text();
    QString toPlace=ui->lineEdit_to_2->text();
    QDate dateline=ui->dateEdit_2->date();
    QString date=QString::number(dateline.year())+"-"+QString::number(dateline.month())+"-"+QString::number(dateline.day());
    QJsonObject searchJson;
    searchJson.insert("request",5);
    searchJson.insert("from",fromPlace);
    searchJson.insert("to",toPlace);
    searchJson.insert("date",date);
    QJsonArray receiveTickets;

    Client::GetInstance()->handleData(searchJson,receiveTickets);

    if(receiveTickets.at(0).toBool()){
        this->ticketsArray=receiveTickets;
         init();

     }else{
        QMessageBox message(QMessageBox::NoIcon, "查询结果", "查询失败.");
        message.exec();
    }
}
