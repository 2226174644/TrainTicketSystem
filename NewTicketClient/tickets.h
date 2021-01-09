#ifndef TICKETS_H
#define TICKETS_H
#include <QDateTime>
#include <QString>

class Tickets
{
public:
    Tickets();
    void setTrainId( QString tId);
    QString getTrainId();
    void setFromPlace(QString place);
    QString getFromPlace();
    void setToPlace(QString place);
    QString getToPlace();
    void setStartTime(QString time);
    QString getStartTime();
    void setArriveTime(QString time);
    QString getArriveTime();
    void setDate(QString date);
    QString getDate();
    void setTicketsNum0(int num);
    int getTicektsNum0();
    void setTicketsNum1(int num);
    int getTicektsNum1();
    void setTicketsNum2(int num);
    int getTicketsNum2();
    void setTicketsPay0(double pay);
    double getTicketsPay0();
    void setTicketsPay1(double pay);
    double getTicketsPay1();
    void setTicketsPay2(double pay);
    double getTicketsPay2();
    QString orderId;
    QDate datePlus;//
private:
    QString trainId;
    QString fromPlace;
    QString toPlace;
    QString startTime;
    QString arriveTime;
    QString date;

    int ticketsNum0;
    int ticketsNum1;
    int ticketsNum2;
    double ticketPay0;
    double ticketPay1;
    double ticketPay2;

};

#endif // TICKETS_H
