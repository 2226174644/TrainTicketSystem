#include "addpassagerui.h"
#include "ui_addpassagerui.h"
#include <QDebug>
#include <QMessageBox>

AddPassagerUi::AddPassagerUi(User user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPassagerUi)
{
    this->user=user;

    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,180);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,100);
    QStringList header;
            header.append(QObject::tr("姓名"));
            header.append(QObject::tr("手机号"));
            header.append(QObject::tr("身份证号"));
            header.append(QObject::tr("类型"));
            header.append(QObject::tr("删除"));
    ui->tableWidget->setHorizontalHeaderLabels(header);
    init();

}
AddPassagerUi::~AddPassagerUi()
{
    delete ui;
}

void AddPassagerUi::init()
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

    passagerNum=user.getPassagersNum();

    ui->tableWidget->clearContents();
    for(int i=0;i<user.getPassagersNum();i++){//循环遍历 插入乘客数据
        //name
        QString name=user.passagers[i].getName();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));

        //phone
        QString phone=user.passagers[i].getphoneNumber();
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(phone));

        //cid
        QString cid=user.passagers[i].getCredentID();
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(cid));

        //type
        QString type=user.passagers[i].getType();
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(type));

        //button
//        buttons[i].setText(tr("删除"));
//        buttons[i].setEnabled(true);
//        ui->tableWidget->setCellWidget(i,4,buttons+i);
        QPushButton* delBtn = new QPushButton;
        delBtn->setText("删除");
        ui->tableWidget->setCellWidget(i,4,delBtn);
        connect(delBtn,SIGNAL(clicked()),this,SLOT(deleteThisRow()));
    }

}

void AddPassagerUi::deleteThisRow()
{
    //
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
            return;
        int x = pushBtn->frameGeometry().x();
        int y = pushBtn->frameGeometry().y();
        QModelIndex index = ui->tableWidget->indexAt(QPoint(x, y));
        int row = index.row();
        int colum = index.column();
        qDebug() << QObject::tr("Remove row, row: %1, colum: %2").arg(row).arg(colum);

     //
      //  ui->tableWidget->setFocus();
//       int row=-1;
//       row=ui->tableWidget->currentRow();
//       qDebug() <<"delete line ："<<row;
       if(row>=0){
          //对数据库的操作 删除乘客
          QJsonObject deletePassager;
          deletePassager.insert("request",3);
          deletePassager.insert("userId",user.getID());
          deletePassager.insert("cid",user.passagers[row].getCredentID());
          QJsonArray deleteBuffer;
          Client::GetInstance()->handleData(deletePassager,deleteBuffer);
          if(deleteBuffer.at(0).toBool()){
              QMessageBox message(QMessageBox::NoIcon,"删除信息","删除成功！");
              message.exec();
              ui->tableWidget->removeRow(row);
              //对本地user进行操作
              user.setPassagersNum(user.getPassagersNum()-1);
              user.passagers[row].setName(NULL);
              user.passagers[row].setphoneNumber(NULL);
              user.passagers[row].setCredentID(NULL);
              user.passagers[row].setType(NULL);


              ui->tableWidget->setRowCount(5);
          }else{
              QMessageBox message(QMessageBox::NoIcon,"删除信息","删除失败！");
              message.exec();
          }
       }


}

void AddPassagerUi::setUser(User &user)
{
        qDebug()<<"setUser";
        this->user=user;

        init();

}

void AddPassagerUi::on_pushButton_add_clicked()
{
    if(user.getPassagersNum()>=5){
        QMessageBox message(QMessageBox::NoIcon,"错误","添加的乘客最多为5位，请先删除！");
        message.exec();
        return;
    }else{
        apd=new AddPassagerDialog(user);
        apd->setWindowTitle("添加乘车人");
        connect(apd,SIGNAL(getUser(User &)),this,SLOT(setUser(User &)));
        apd->exec();
        init();
    }
}
