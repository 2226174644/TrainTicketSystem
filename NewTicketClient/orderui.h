#ifndef ORDERUI_H
#define ORDERUI_H

#include <QJsonArray>
#include <QMainWindow>
#include "user.h"
#include "orderdetail.h"
namespace Ui {
class OrderUi;
}

class OrderUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderUi(User user,QWidget *parent = nullptr);
    ~OrderUi();

private:
    Ui::OrderUi *ui;
    User user;
    QString *order;
    QJsonArray orderArray;
    OrderDetail *orderDetail;
    void init();
private  slots:
    void detailThisRow();

};

#endif // ORDERUI_H
