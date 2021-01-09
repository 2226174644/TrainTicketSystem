#ifndef ADDPASSAGERUI_H
#define ADDPASSAGERUI_H

#include <QMainWindow>
#include <QPushButton>
#include "user.h"
#include "addpassagerdialog.h"
#include "client.h"
namespace Ui {
class AddPassagerUi;
}

class AddPassagerUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddPassagerUi(User user,QWidget *parent = nullptr);
    ~AddPassagerUi();

    void init();

private slots:
    void on_pushButton_add_clicked();

    void deleteThisRow();
    void setUser(User &);
private:
    Ui::AddPassagerUi *ui;
    AddPassagerDialog *apd;
    User user;
    int passagerNum;
};

#endif // ADDPASSAGERUI_H
