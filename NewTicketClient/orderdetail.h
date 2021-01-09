#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include "user.h"
#include "switchorderdialog.h"
namespace Ui {
class OrderDetail;
}

class OrderDetail : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDetail(User user,QJsonObject orderObject,QString orderId,QWidget *parent = nullptr);
    ~OrderDetail();

private:
    Ui::OrderDetail *ui;
    QJsonArray detailArray;
    QString orderId;
    QString trainId;
    QString fromStation ;
    QString toStation ;
    QString orderStatus;

    int *status;
    SwitchOrderDialog *switchDialog;

    void init();

private slots:
    void cancelOrder();
    void switchOrder();
    void on_buttonBox_accepted();
};

#endif // ORDERDETAIL_H
