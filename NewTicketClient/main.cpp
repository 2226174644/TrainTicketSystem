#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    a.setFont(QFont("Microsoft Yahei", 9));

    a.setWindowIcon(QIcon(":/12306.ico"));

    QFile qss(":silvery.css");

           if( qss.open(QFile::ReadOnly))

           {

               qDebug("open success");

               QString style = QLatin1String(qss.readAll());

               a.setStyleSheet(style);

               qss.close();

           }

           else

           {

              qDebug("Open failed");

     }

    MainWindow w;
    w.setWindowTitle("火车站售票系统");
    w.show();

    return a.exec();
}
