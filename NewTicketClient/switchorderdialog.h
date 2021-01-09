#ifndef SWITCHORDERDIALOG_H
#define SWITCHORDERDIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QComboBox>
#include "tickets.h"
namespace Ui {
class SwitchOrderDialog;
}

class SwitchOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SwitchOrderDialog(QString orderId,QJsonObject orderObject,QJsonArray ticketsArray,QWidget *parent = nullptr);
    ~SwitchOrderDialog();

private:
    Ui::SwitchOrderDialog *ui;
    Tickets *tickets;
    QJsonArray ticketsArray;
    QJsonObject tempOrder;
    QString orderId;
    void init();
private slots:
    void switchTicket();
    void on_pushButton_search_2_clicked();
};

#endif // SWITCHORDERDIALOG_H
