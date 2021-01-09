#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "user.h"
#include "userui.h"
#include "registerUi.h"
#include "ticketsui.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    registerUi *regUi=nullptr;
    UserUI *userUi=nullptr;
    TicketsUi  *ticketsUi=nullptr;
    User user;


private slots:
    void on_loginButton_clicked();

    void on_searchButton_clicked();

    void on_pushButton_moreInfo_clicked();

    void on_pushButton_register_clicked();

   // void onCloseDeleletRegUi();
    void on_pushButton_exit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
