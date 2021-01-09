#include "userui.h"
#include "ui_userui.h"

UserUI::UserUI(User user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserUI)
{
    this->user=user;
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);
    ui->label_name->setText(user.getName());
    ui->label_id->setText(user.getID());
    ui->label_cid->setText(user.getCredentID());
    ui->label_sex->setText(user.getSex());
  //  ui->label_amount->setText(QString::number(user.getAmount(), 'f', 2));
    ui->label_phoneNumber->setText(user.getphoneNumber());
    ui->label_type->setText(user.getType());
    ui->label_she->setVisible(false);
    if(ui->label_sex->text()=="女"){
        ui->label_he->setVisible(false);
        ui->label_she->setVisible(true);
    }
}

UserUI::~UserUI()
{
    delete ui;
}

void UserUI::on_pushButton_order_clicked()
{
    orderUi=new OrderUi(user);
    orderUi->setWindowTitle("历史订单");
    orderUi->show();
}

void UserUI::on_pushButton_passager_clicked()
{
    addPassager=new AddPassagerUi(user);
    addPassager->setWindowTitle("设置乘车人");
    addPassager->show();
}
