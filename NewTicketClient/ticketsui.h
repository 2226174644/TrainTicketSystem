#ifndef TICKETSUI_H
#define TICKETSUI_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include "tickets.h"
#include "user.h"
#include "ticketdetail.h"
namespace Ui {
class TicketsUi;
}

class TicketsUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicketsUi(User user,QJsonArray ticketsArray,QString from,QString to,QDate date,QWidget *parent = nullptr);
    ~TicketsUi();
    TicketDetail *ticketDetailUI=nullptr;
    TicketDetail *ticketDetailUI2=nullptr;
protected slots:
    void buyTicket();
    void transferTicket();
private slots:
    void on_pushButton_search_clicked();
    void setOrder(QString &);

private:
    Ui::TicketsUi *ui;
    Tickets *tickets;
    Tickets *transferTickets;
    User user;
    QString dateString;
    QJsonArray ticketsArray;
    QJsonArray transferArray;
    QDate date;
    int rowFlag=-1;
    void init();

    //QPushButton *buttons;

};

#endif // TICKETSUI_H
