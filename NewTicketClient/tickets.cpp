#include "tickets.h"

Tickets::Tickets()
{

}

void Tickets::setTrainId( QString tId)
{
    trainId=tId;
}

QString Tickets::getTrainId()
{
    return trainId;
}

void Tickets::setFromPlace(QString place)
{
    fromPlace=place;
}

QString Tickets::getFromPlace()
{
    return fromPlace;
}

void Tickets::setToPlace(QString place)
{
    toPlace=place;
}

QString Tickets::getToPlace()
{
    return toPlace;
}

void Tickets::setStartTime(QString time)
{
    startTime=time;
}

QString Tickets::getStartTime()
{
    return startTime;
}

void Tickets::setArriveTime(QString time)
{
    arriveTime=time;
}

QString Tickets::getArriveTime()
{
    return  arriveTime;
}

void Tickets::setDate(QString date)
{
    this->date=date;
}

QString Tickets::getDate()
{
    return  date;
}

void Tickets::setTicketsNum0(int num)
{
    ticketsNum0=num;
}

int Tickets::getTicektsNum0()
{
    return ticketsNum0;
}

void Tickets::setTicketsNum1(int num)
{
    ticketsNum1=num;
}

int Tickets::getTicektsNum1()
{
    return ticketsNum1;
}

void Tickets::setTicketsNum2(int num)
{
    ticketsNum2=num;
}

int Tickets::getTicketsNum2()
{
    return ticketsNum2;
}

void Tickets::setTicketsPay0(double pay)
{
    ticketPay0=pay;
}

double Tickets::getTicketsPay0()
{
    return ticketPay0;
}

void Tickets::setTicketsPay1(double pay)
{
    ticketPay1=pay;
}

double Tickets::getTicketsPay1()
{
    return ticketPay1;
}

void Tickets::setTicketsPay2(double pay)
{
    ticketPay2=pay;
}

double Tickets::getTicketsPay2()
{
    return ticketPay2;
}
