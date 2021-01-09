#ifndef USERUI_H
#define USERUI_H
#include"user.h"
#include <QMainWindow>
#include "orderui.h"
#include "addpassagerui.h"

namespace Ui {
class UserUI;
}

class UserUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserUI(User user,QWidget *parent = nullptr);
    ~UserUI();

private slots:
    void on_pushButton_order_clicked();

    void on_pushButton_passager_clicked();

private:
    Ui::UserUI *ui;
    OrderUi *orderUi=nullptr;
    AddPassagerUi *addPassager=nullptr;
    User user;
};

#endif // USERUI_H
