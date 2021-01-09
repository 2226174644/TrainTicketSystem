#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCloseEvent>
#include "client.h"

namespace Ui {
class registerUi;
}

class registerUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit registerUi(QWidget *parent = nullptr);
    ~registerUi();
    QRegExp *regx1;
    QRegExp *regx2;
    void closeEvent(QCloseEvent *event);
private slots:
    void on_enterButton_clicked();

private:
    Ui::registerUi *ui;

signals:
   void signalClose();
};

#endif // REGISTER_H
