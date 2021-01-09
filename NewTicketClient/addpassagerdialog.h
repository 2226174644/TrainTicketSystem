#ifndef ADDPASSAGERDIALOG_H
#define ADDPASSAGERDIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include "client.h"
#include "user.h"
namespace Ui {
class AddPassagerDialog;
}

class AddPassagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPassagerDialog(User user,QWidget *parent = nullptr);
    ~AddPassagerDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddPassagerDialog *ui;
    User user;
    QRegExp *regx1;
    QRegExp *regx2;

signals:
    void getUser(User &user);
};

#endif // ADDPASSAGERDIALOG_H
