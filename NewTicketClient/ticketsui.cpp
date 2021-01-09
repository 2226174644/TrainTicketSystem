#include "ticketsui.h"
#include "ui_ticketsui.h"
#include "QDebug"

#include <qmessagebox.h>


TicketsUi::TicketsUi(User user, QJsonArray ticketsArray, QString from, QString to,QDate date, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicketsUi)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    this->user=user;
    this->ticketsArray=ticketsArray;
    this->date=date;
    ui->lineEdit_from->setText(from);
    ui->lineEdit_to->setText(to);
    ui->dateEdit->setDate(date);
    dateString=QString::number(date.year())+"-"+QString::number(date.month())+"-"+QString::number(date.day());
    //初始化表
    ui->ticketsTable->setWindowTitle("车次列表");
    ui->ticketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ticketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ticketsTable->setColumnCount(8);

    //设置列宽
    ui->ticketsTable->setColumnWidth(0,120);
    ui->ticketsTable->setColumnWidth(1,150);
    ui->ticketsTable->setColumnWidth(2,150);
    ui->ticketsTable->setColumnWidth(3,75);
    ui->ticketsTable->setColumnWidth(4,50);
    ui->ticketsTable->setColumnWidth(5,50);
    ui->ticketsTable->setColumnWidth(6,50);
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


    //换乘表
    ui->tableWidget->setColumnCount(9);
    QStringList header1;
    header1.append(QObject::tr(""));
    header1.append(QObject::tr("车次"));
    header1.append(QObject::tr("出发站-到达站"));
    header1.append(QObject::tr("出发时间-到达时间"));
    header1.append(QObject::tr("历时"));
    header1.append(QObject::tr("商务座"));
    header1.append(QObject::tr("一等座"));
    header1.append(QObject::tr("二等座"));
    header1.append(QObject::tr("备注"));
    ui->tableWidget->setHorizontalHeaderLabels(header1);

    ui->tableWidget->setWindowTitle("车次列表");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);


    //设置列宽
    ui->tableWidget->setColumnWidth(0,25);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,75);
    ui->tableWidget->setColumnWidth(5,50);
    ui->tableWidget->setColumnWidth(6,50);
    ui->tableWidget->setColumnWidth(7,50);
    ui->tableWidget->setColumnWidth(8,75);
    //设置行
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->hide();

    init();

}
TicketsUi::~TicketsUi()
{

    delete ui;
}

void TicketsUi::buyTicket()
{
    //
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->ticketsTable->indexAt(QPoint(x, y));
    int row = index.row();
    int colum = index.column();
    qDebug() << QObject::tr("output row, row: %1, colum: %2").arg(row).arg(colum);
     //      
    if(row>=0){
//        qDebug() << tickets[row]->getTrainId();
        qDebug() << "clicked" << row << " ";
        Tickets ticket;
        ticket.setTrainId(tickets[row].getTrainId());
        ticket.setFromPlace(tickets[row].getFromPlace());
        ticket.setToPlace(tickets[row].getToPlace());
        ticket.setStartTime(tickets[row].getStartTime());
        ticket.setArriveTime(tickets[row].getArriveTime());
        ticket.setTicketsNum0(tickets[row].getTicektsNum0());
        ticket.setTicketsNum1(tickets[row].getTicektsNum1());
        ticket.setTicketsNum2(tickets[row].getTicketsNum2());
        ticket.setTicketsPay0(tickets[row].getTicketsPay0());
        ticket.setTicketsPay1(tickets[row].getTicketsPay1());
        ticket.setTicketsPay2(tickets[row].getTicketsPay2());
        ticket.setDate(dateString);
        ticket.datePlus=tickets[row].datePlus;

        ticketDetailUI=new TicketDetail(user, ticket);
        ticketDetailUI->setWindowTitle("车票详情");
        ticketDetailUI->show();
    }
}

void TicketsUi::transferTicket()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    int colum = index.column();
    qDebug() << QObject::tr("output row, row: %1, colum: %2").arg(row).arg(colum);
     //
    if(row>=0){
//        qDebug() << tickets[row]->getTrainId();
        qDebug() << "clicked" << row << " ";
        Tickets ticket;
        ticket.setTrainId(transferTickets[row].getTrainId());
        ticket.setFromPlace(transferTickets[row].getFromPlace());
        ticket.setToPlace(transferTickets[row].getToPlace());
        ticket.setStartTime(transferTickets[row].getStartTime());
        ticket.setArriveTime(transferTickets[row].getArriveTime());
        ticket.setTicketsNum0(transferTickets[row].getTicektsNum0());
        ticket.setTicketsNum1(transferTickets[row].getTicektsNum1());
        ticket.setTicketsNum2(transferTickets[row].getTicketsNum2());
        ticket.setTicketsPay0(transferTickets[row].getTicketsPay0());
        ticket.setTicketsPay1(transferTickets[row].getTicketsPay1());
        ticket.setTicketsPay2(transferTickets[row].getTicketsPay2());
        ticket.setDate(dateString);
        ticket.datePlus=transferTickets[row].datePlus;

        rowFlag=row+1;
        ticketDetailUI=new TicketDetail(user, ticket);
        ticketDetailUI->setWindowTitle("车票详情");
        ticketDetailUI->show();

        connect(ticketDetailUI,SIGNAL(getOrder(QString &)),this,SLOT(setOrder(QString &)));
    }
}

void TicketsUi::on_pushButton_search_clicked()
{      if(ui->lineEdit_from->text()==""){
        QMessageBox message(QMessageBox::NoIcon, "提示", "未填写出发地.");
        message.exec();
        return;
        }
       if(ui->lineEdit_to->text()==""){
         QMessageBox message(QMessageBox::NoIcon, "提示", "未填写目的地.");
         message.exec();
         return;
        }
        QJsonObject searchJson;
        searchJson.insert("request",5);
        searchJson.insert("from",ui->lineEdit_from->text());
        searchJson.insert("to",ui->lineEdit_to->text());
        QDate dateTemp=ui->dateEdit->date();
        dateString=QString::number(dateTemp.year())+"-"+QString::number(dateTemp.month())+"-"+QString::number(dateTemp.day());
        searchJson.insert("date",dateString);
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

void TicketsUi::setOrder(QString &order)
{
    if(rowFlag==-1) return;
    transferTickets[rowFlag].orderId=order;
    if(transferTickets[rowFlag].orderId!=""){
    Tickets ticket2;
    ticket2.setTrainId(transferTickets[rowFlag].getTrainId());
    ticket2.setFromPlace(transferTickets[rowFlag].getFromPlace());
    ticket2.setToPlace(transferTickets[rowFlag].getToPlace());
    ticket2.setStartTime(transferTickets[rowFlag].getStartTime());
    ticket2.setArriveTime(transferTickets[rowFlag].getArriveTime());
    ticket2.setTicketsNum0(transferTickets[rowFlag].getTicektsNum0());
    ticket2.setTicketsNum1(transferTickets[rowFlag].getTicektsNum1());
    ticket2.setTicketsNum2(transferTickets[rowFlag].getTicketsNum2());
    ticket2.setTicketsPay0(transferTickets[rowFlag].getTicketsPay0());
    ticket2.setTicketsPay1(transferTickets[rowFlag].getTicketsPay1());
    ticket2.setTicketsPay2(transferTickets[rowFlag].getTicketsPay2());
    ticket2.setDate(dateString);
    ticket2.datePlus=transferTickets[rowFlag].datePlus;
    ticket2.orderId=order;

    ticketDetailUI2=new TicketDetail(user, ticket2);
    ticketDetailUI2->setWindowTitle("车票详情");
    ticketDetailUI2->show();
    }else {
        QMessageBox message(QMessageBox::NoIcon, "结果", "order null.");
        message.exec();
}
}

void TicketsUi::init()
{
    //初始化数据
    tickets=new Tickets[ticketsArray.size()-1];
    ui->ticketsTable->clearContents();
    ui->ticketsTable->setRowCount(ticketsArray.size()-1);
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
    }
    //buttons =new QPushButton[ticketsArray.size()];



    for(int i=0;i<ticketsArray.size()-1;i++){

        QString temp = tickets[i].getTrainId();
        //车次
        ui->ticketsTable->setItem(i,0,new QTableWidgetItem(temp));

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
        int secs;
        if(time1<time2){
        secs=time1.secsTo(time2);
        }else{
        secs=time2.secsTo(time1);
        }
        int h=secs/3600;
        int m=(secs%3600)/60;

        //应补丁
        if(h>=12){
         h=(-secs+86400)/3600;
         m=((-secs+86400)%3600)/60;
         tickets[i].datePlus=date.addDays(1);
        }

        QString time=QString::number(h)+" h "+QString::number(m)+" m ";
        ui->ticketsTable->setItem(i,3,new QTableWidgetItem(time));

        double price=(h*60+m)*1.5;
        tickets[i].setTicketsPay2(price);
        tickets[i].setTicketsPay1(price*1.5);
        tickets[i].setTicketsPay0(price*3);

        //商务座，一等座，二等座

        ui->ticketsTable->setItem(i,4,new QTableWidgetItem(QString::number(tickets[i].getTicektsNum0())));
        ui->ticketsTable->setItem(i,5,new QTableWidgetItem(QString::number(tickets[i].getTicektsNum1())));
        ui->ticketsTable->setItem(i,6,new QTableWidgetItem(QString::number(tickets[i].getTicketsNum2())));

        //购票按钮
        QPushButton *button =new QPushButton();
        button->setText(tr("购票"));
        button->setEnabled(true);
        ui->ticketsTable->setCellWidget(i,7,button);
        connect(button,SIGNAL(clicked()),this,SLOT(buyTicket()));
    }


    //换乘数据
    ui->tableWidget->clearContents();

    QJsonObject searchJson;
    searchJson.insert("request",13);
    searchJson.insert("from",ui->lineEdit_from->text());
    searchJson.insert("to",ui->lineEdit_to->text());
    QDate dateTemp=ui->dateEdit->date();
    dateString=QString::number(dateTemp.year())+"-"+QString::number(dateTemp.month())+"-"+QString::number(dateTemp.day());
    searchJson.insert("date",dateString);
    QJsonArray transferBuffer;
    Client::GetInstance()->handleData(searchJson,transferBuffer);
    this->transferArray=transferBuffer;

    ui->tableWidget->setRowCount(transferArray.size());

    transferTickets=new Tickets[transferArray.size()];
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(transferArray.size());
    for(int i=0;i<transferArray.size();i++){
        QJsonObject temp;
        temp=transferArray.at(i).toObject();
        transferTickets[i].setTrainId(temp.value("tId").toString());
        transferTickets[i].setFromPlace(temp.value("from").toString());
        transferTickets[i].setToPlace(temp.value("to").toString());
        transferTickets[i].setStartTime(temp.value("startTime").toString());
        transferTickets[i].setArriveTime(temp.value("arriveTime").toString());
        transferTickets[i].setTicketsNum0(temp.value("ticketsNum0").toInt());
        transferTickets[i].setTicketsNum1(temp.value("ticketsNum1").toInt());
        transferTickets[i].setTicketsNum2(temp.value("ticketsNum2").toInt());
    }

    int count=1;
    for(int i=0;i<transferArray.size()-1;i=i+2){


        ui->tableWidget->setSpan(i,0,2,1);
        ui->tableWidget->setSpan(i,8,2,1);

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(count)));

        //购票按钮
        QPushButton *button =new QPushButton();
        button->setText(tr("购票"));
        button->setEnabled(true);
        ui->tableWidget->setCellWidget(i,8,button);
        connect(button,SIGNAL(clicked()),this,SLOT(transferTicket()));
        count++;


        //车次
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(transferTickets[i].getTrainId()));
        ui->tableWidget->setItem(i+1,1,new QTableWidgetItem(transferTickets[i+1].getTrainId()));

        //始发地-目的地
        QString from=transferTickets[i].getFromPlace();
        QString to=transferTickets[i].getToPlace();
        QString from_to=from+"-"+to;
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(from_to));

        QString from1=transferTickets[i+1].getFromPlace();
        QString to1=transferTickets[i+1].getToPlace();
        QString from_to1=from1+"-"+to1;
        ui->tableWidget->setItem(i+1,2,new QTableWidgetItem(from_to1));

        //出发时间-到达时间
        QString start_arrive=transferTickets[i].getStartTime()+"-"+transferTickets[i].getArriveTime();
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(start_arrive));
        QString start_arrive1=transferTickets[i+1].getStartTime()+"-"+transferTickets[i+1].getArriveTime();
        ui->tableWidget->setItem(i+1,3,new QTableWidgetItem(start_arrive1));

        //历时
        if(true){
        QDateTime time1=QDateTime::fromString(transferTickets[i].getStartTime(),"hh:mm:ss");
        QDateTime time2=QDateTime::fromString(transferTickets[i].getArriveTime(),"hh:mm:ss");
        int secs;
        if(time1<time2){
        secs=time1.secsTo(time2);
        }else{
        secs=time2.secsTo(time1);
        }
        int h=secs/3600;
        int m=(secs%3600)/60;
        if(h>=12){
         h=(-secs+86400)/3600;
         m=((-secs+86400)%3600)/60;
         transferTickets[i].datePlus=date.addDays(1);
        }
        QString time=QString::number(h)+" h "+QString::number(m)+" m ";
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(time));
        double price=(h*60+m)*1.5;
        transferTickets[i].setTicketsPay2(price);
        transferTickets[i].setTicketsPay1(price*1.5);
        transferTickets[i].setTicketsPay0(price*3);
        }

        if(true){
        QDateTime time1=QDateTime::fromString(transferTickets[i+1].getStartTime(),"hh:mm:ss");
        QDateTime time2=QDateTime::fromString(transferTickets[i+1].getArriveTime(),"hh:mm:ss");
        int secs;
        if(time1<time2){
        secs=time1.secsTo(time2);
        }else{
        secs=time2.secsTo(time1);
        }
        int h=secs/3600;
        int m=(secs%3600)/60;
        if(h>=12){
         h=(-secs+86400)/3600;
         m=((-secs+86400)%3600)/60;
         transferTickets[i+1].datePlus=date.addDays(1);
        }
        QString time=QString::number(h)+" h "+QString::number(m)+" m ";
        ui->tableWidget->setItem(i+1,4,new QTableWidgetItem(time));
        double price=(h*60+m)*1.5;
        transferTickets[i+1].setTicketsPay2(price);
        transferTickets[i+1].setTicketsPay1(price*1.5);
        transferTickets[i+1].setTicketsPay0(price*3);
        }

        //商务座，一等座，二等座

        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(transferTickets[i].getTicektsNum0())));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(transferTickets[i].getTicektsNum1())));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(transferTickets[i].getTicketsNum2())));
        ui->tableWidget->setItem(i+1,5,new QTableWidgetItem(QString::number(transferTickets[i+1].getTicektsNum0())));
        ui->tableWidget->setItem(i+1,6,new QTableWidgetItem(QString::number(transferTickets[i+1].getTicektsNum1())));
        ui->tableWidget->setItem(i+1,7,new QTableWidgetItem(QString::number(transferTickets[i+1].getTicketsNum2())));

    }


}
