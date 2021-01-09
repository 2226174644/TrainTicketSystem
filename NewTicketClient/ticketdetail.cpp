#include "ticketdetail.h"
#include "ui_ticketdetail.h"

#include <QDebug>
#include <qmessagebox.h>

TicketDetail::TicketDetail(User user, Tickets tickets, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicketDetail)
{

    QJsonObject loginJson;
    loginJson.insert("request",8);
    loginJson.insert("uid",user.getID());
//    loginJson.insert("psw",user.getPsw());

    QJsonArray confirmBuffer;
    Client::GetInstance()->handleData(loginJson,confirmBuffer);

    //加载乘车人
     int passagersNum=confirmBuffer.size();
     qDebug()<<"passagerNUm:"<<passagersNum;
     user.setPassagersNum(passagersNum);
     user.passagers=new User[5];

     for(int i=0;i<confirmBuffer.size();i++){
      QJsonObject temp;
      temp=confirmBuffer.at(i).toObject();
      user.passagers[i].setName(temp.value("name").toString());
      user.passagers[i].setCredentID(temp.value("cId").toString());
      user.passagers[i].setphoneNumber(temp.value("phone").toString());
      user.passagers[i].setType(temp.value("type").toString());
        }
    this->user=user;

    this->tickets=tickets;
    ui->setupUi(this);
    ui->label_dateFrom->setText(tickets.getDate());
    if(tickets.datePlus.isNull()){
        ui->label_dateTo->setText(tickets.getDate());
    }else{
        ui->label_dateTo->setText(QString::number(tickets.datePlus.year())+"-"+QString::number(tickets.datePlus.month())+"-"+QString::number(tickets.datePlus.day()));
    }

    ui->checkBox_1->setVisible(false);
    ui->checkBox_2->setVisible(false);
    ui->checkBox_3->setVisible(false);
    ui->checkBox_4->setVisible(false);
    ui->checkBox_5->setVisible(false);
    //初始化ui
    ui->label_from->setText(tickets.getFromPlace());
    ui->label_to->setText(tickets.getToPlace());
    ui->label_startTime->setText(tickets.getStartTime());
    ui->label_arriveTime->setText(tickets.getArriveTime());
    ui->label_trainId->setText(tickets.getTrainId());
    QString info0="商务座：(￥"+QString::number(tickets.getTicketsPay0())+") "+QString::number(tickets.getTicektsNum0())+"张";
    QString info1="一等座：(￥"+QString::number(tickets.getTicketsPay1())+") "+QString::number(tickets.getTicektsNum1())+"张";
    QString info2="二等座：(￥"+QString::number(tickets.getTicketsPay2())+") "+QString::number(tickets.getTicketsNum2())+"张";
    ui->label_zeroInfo->setText(info0);
    ui->label_firstInfo->setText(info1);
    ui->label_secondInfo->setText(info2);
    //生成乘车人的checkbox
    ui->checkBox->setText(user.getName());
    //    QPoint checkPoint(ui->checkBox->mapToParent(QPoint(0,0)));
    //    int x=checkPoint.x();
    //    int y=checkPoint.y();
    //    //输出
    //    qDebug()<<"x:"+QString::number(x)+"   "+"y:"+QString::number(y);
    //checkBox
    if(user.getPassagersNum()>0){
        // QCheckBox *passagerboxs=new QCheckBox[user.getPassagersNum()];

        //         passagerboxs->setParent(ui->scrollArea);
        //         passagerboxs[i].setGeometry(x+90*(i%5+1),y+25*(i/5),80,15);
        //        //
        //         qDebug()<<"输出添加的chex坐标:";
        //         qDebug()<<"x:"+QString::number(x+90*(i%5+1))+"   "+"y:"+QString::number(y+25*(i/5),80,15);
        //        passagerboxs[i].setText(user.passagers[i].getName());
        //        passagerboxs[i].show();
        //        //生成/隐藏
        //        connect(passagerboxs+i,SIGNAL(checked(bool)),this,SLOT(onBoxClicked(bool)));
        if(!user.passagers[0].getName().isNull()){
            ui->checkBox_1->setText(user.passagers[0].getName());
            ui->checkBox_1->setVisible(true);
        }
        if(!user.passagers[1].getName().isNull()){
            ui->checkBox_2->setText(user.passagers[1].getName());
            ui->checkBox_2->setVisible(true);
        }
        if(!user.passagers[2].getName().isNull()){
            ui->checkBox_3->setText(user.passagers[2].getName());
            ui->checkBox_3->setVisible(true);
        }
        if(!user.passagers[3].getName().isNull()){
            ui->checkBox_4->setText(user.passagers[3].getName());
            ui->checkBox_4->setVisible(true);
        }
        if(!user.passagers[4].getName().isNull()){
            ui->checkBox_5->setText(user.passagers[4].getName());
            ui->checkBox_5->setVisible(true);
        }
    }
    //表格
    ui->passagerTable->verticalHeader()->hide();

    ui->passagerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->passagerTable->setColumnCount(5);
    ui->passagerTable->setRowCount(user.getPassagersNum()+1);
    ui->passagerTable->setColumnWidth(0,80);
    ui->passagerTable->setColumnWidth(1,80);
    ui->passagerTable->setColumnWidth(2,80);
    ui->passagerTable->setColumnWidth(3,190);
    ui->passagerTable->setColumnWidth(4,110);
    QStringList header;
    header.append(QObject::tr("票种"));
    header.append(QObject::tr("席别"));
    header.append(QObject::tr("姓名"));
    header.append(QObject::tr("证件号"));
    header.append(QObject::tr("手机号"));
    ui->passagerTable->setHorizontalHeaderLabels(header);



    userRow=0;
    //票种
    if(user.getType()=="学生"){
        passagerTypes[0].addItem(QObject::tr("成人票"));
        passagerTypes[0].addItem(QObject::tr("学生票"));
    }
    else{
        passagerTypes[0].addItem(QObject::tr("成人票"));
    }
    passagerTypes[0].setEnabled(true);
    ui->passagerTable->setCellWidget(userRow,0,passagerTypes);

    //席别
    if(tickets.getTicketsNum2()!=0){
    chairTypes[0].addItem(QObject::tr("二等座"));
    }
    if(tickets.getTicektsNum1()!=0){
    chairTypes[0].addItem(QObject::tr("一等座"));
    }
    if(tickets.getTicektsNum0()!=0){
    chairTypes[0].addItem(QObject::tr("商务座"));
    }

    chairTypes[0].setEnabled(true);
    ui->passagerTable->setCellWidget(userRow,1,chairTypes);

    //姓名
    QString name=user.getName();
    ui->passagerTable->setItem(userRow,2,new QTableWidgetItem(name));
    //证件号
    QString cId=user.getCredentID();
    ui->passagerTable->setItem(userRow,3,new QTableWidgetItem(cId));
    //手机号
    QString phoneNum=user.getphoneNumber();
    ui->passagerTable->setItem(userRow,4,new QTableWidgetItem(phoneNum));

    //ui->passagerTable->setRowHidden(0, false);

    ui->passagerTable->hideRow(userRow);

    //乘客
    if(user.getPassagersNum()>0){
        for(int i=1;i<=user.getPassagersNum();i++){
            addTicketsType(i,i);
            addChair(i,i);
            addName(i,i-1);
            addCid(i,i-1);
            addPhone(i,i-1);
            ui->passagerTable->hideRow(i);
        }
    }

    // 初始化乘客状态
    for(int i=0;i<6;i++){
        status[i]=0;
    }




}

TicketDetail::~TicketDetail()
{
    delete ui;
}

void TicketDetail::addTicketsType(int row,int i)
{
    if(user.passagers[i-1].getType()=="学生"){
        passagerTypes[i].addItem(QObject::tr("成人票"));
        passagerTypes[i].addItem(QObject::tr("学生票"));
    }else{
        passagerTypes[i].addItem(QObject::tr("成人票"));
    }

    passagerTypes[i].setEnabled(true);
    ui->passagerTable->setCellWidget(row,0,passagerTypes+i);
}

void TicketDetail::addChair(int row,int i)
{
    if(tickets.getTicketsNum2()!=0){
    chairTypes[i].addItem(QObject::tr("二等座"));
    }
    if(tickets.getTicektsNum1()!=0){
    chairTypes[i].addItem(QObject::tr("一等座"));
    }
    if(tickets.getTicektsNum0()!=0){
    chairTypes[i].addItem(QObject::tr("商务座"));
    }
    chairTypes[i].setEnabled(true);
    ui->passagerTable->setCellWidget(row,1,chairTypes+i);
}

void TicketDetail::addName(int row,int i)
{
    QString name=user.passagers[i].getName();
    ui->passagerTable->setItem(row,2,new QTableWidgetItem(name));
}

void TicketDetail::addCid(int row, int i)
{
    QString cId=user.passagers[i].getCredentID();
    ui->passagerTable->setItem(row,3,new QTableWidgetItem(cId));
}

void TicketDetail::addPhone(int row, int i)
{
    QString phoneNum=user.passagers[i].getphoneNumber();
    ui->passagerTable->setItem(row,4,new QTableWidgetItem(phoneNum));
}

void TicketDetail::removeThis(int row)
{
    ui->passagerTable->hideRow(row);
    qDebug()<<"end currentRow："<<ui->passagerTable->rowCount();

    //    passagerTypes->removeAt(row-1);
    //    chairTypes->removeAt(row-1);
}



void TicketDetail::on_checkBox_clicked(bool checked)
{



    if(checked){
        status[0]=1;
        ui->passagerTable->showRow(userRow);

    }else{
        status[0]=0;
        ui->passagerTable->hideRow(userRow);


    }
}

void TicketDetail::on_checkBox_1_clicked(bool checked)
{

    if(checked){
        status[1]=1;
        ui->passagerTable->showRow(p1Row);

    }else{
        status[1]=0;
        removeThis(p1Row);
    }
}
//

//
void TicketDetail::on_checkBox_2_clicked(bool checked)
{
    //    p2Row=2;
    //    addTicketsType(p2Row,1);
    //    addChair(p2Row,1);
    //    addName(p2Row,0);
    //    addCid(p2Row,0);
    //    addPhone(p2Row,0);
    //    ui->passagerTable->hideRow(p2Row);
    if(checked){
        status[2]=1;
        ui->passagerTable->showRow(p2Row);


    }else{
        status[2]=0;
        removeThis(p2Row);
    }
}

void TicketDetail::on_checkBox_3_clicked(bool checked)
{
    if(checked){
        status[3]=1;
        ui->passagerTable->showRow(p3Row);
    }else{
        status[3]=0;
        removeThis(p3Row);
    }
}

void TicketDetail::on_checkBox_4_clicked(bool checked)
{
    if(checked){
        status[4]=1;
        ui->passagerTable->showRow(p4Row);
    }else{
        status[4]=0;
        removeThis(p4Row);
    }
}

void TicketDetail::on_checkBox_5_clicked(bool checked)
{
    if(checked){
        status[5]=1;
        ui->passagerTable->showRow(p5Row);
    }else{
        status[5]=0;
        removeThis(p5Row);
    }
}

void TicketDetail::on_pushButton_back_clicked()
{
    this->close();
}

void TicketDetail::on_pushButton_confirm_clicked()
{
    int people=0;
    for(int i=0;i<6;i++){
        if(status[i]==1){
            people++;
        }
    }
    if(people<=0){
        QMessageBox message(QMessageBox::NoIcon,"提示", "未选择乘客.");
        message.exec();

    }else{
        ord =new OrderConfirmUi(user,tickets,passagerTypes,chairTypes,status);
        connect(ord,SIGNAL(confirmButton(QString &)),this,SLOT(closeThis(QString &)));
        ord->setWindowTitle("确认订单");
        ord->show();
    }
}

void TicketDetail::closeThis(QString &order)
{   emit getOrder(order);
    this->close();
}
