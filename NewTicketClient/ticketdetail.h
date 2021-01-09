#ifndef TICKETDETAIL_H
#define TICKETDETAIL_H

#include <QComboBox>
#include <QMainWindow>

#include "tickets.h"
#include "user.h"
#include "orderconfirmui.h"
namespace Ui {
class TicketDetail;
}

class TicketDetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicketDetail(User user,Tickets tickets,QWidget *parent = nullptr);
    ~TicketDetail();

//    QList <QComboBox> *passagerTypes;
//    QList <QComboBox> *chairTypes;

    void addTicketsType(int row,int i);
    void addChair(int row,int i);
    void addName(int row,int i);
    void addCid(int row,int i);
    void addPhone(int row,int i);
    void removeThis(int row);

private slots:
    void on_checkBox_clicked(bool checked);

    void on_checkBox_1_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_pushButton_back_clicked();

    void on_pushButton_confirm_clicked();

    void closeThis(QString &);

private:
    Ui::TicketDetail *ui;
    OrderConfirmUi *ord;
    User user;
    Tickets tickets;

    int userRow=0;
    int p1Row=1;
    int p2Row=2;
    int p3Row=3;
    int p4Row=4;
    int p5Row=5;

    QComboBox passagerTypes[6];
    QComboBox chairTypes[6];

    int status[6];
//protected slots:
//    void onBoxClicked (bool checked);
signals:
    void getOrder(QString & order);
};

#endif // TICKETDETAIL_H
