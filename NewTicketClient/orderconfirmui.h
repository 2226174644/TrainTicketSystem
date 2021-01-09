#ifndef ORDERCONFIRMUI_H
#define ORDERCONFIRMUI_H

#include <QDialog>
#include <QComboBox>
#include <QJsonArray>
#include <QJsonObject>
#include "user.h"
#include "tickets.h"
#include "client.h"
namespace Ui {
class OrderConfirmUi;
}

class OrderConfirmUi : public QDialog
{
    Q_OBJECT

public:
    explicit OrderConfirmUi(User user,Tickets ticket,QComboBox passagerTypes[],QComboBox chairTypes[],int status[],QWidget *parent = nullptr);
    ~OrderConfirmUi();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OrderConfirmUi *ui;
    User user;
    Tickets ticket;
    QComboBox *chairType;
    QComboBox *passagerType;
    double price[6];
    double sum=0.0;
    int num0=0;
    int num1=0;
    int num2=0;
    int *status;
signals:
    void confirmButton(QString &order);
};

#endif // ORDERCONFIRMUI_H
