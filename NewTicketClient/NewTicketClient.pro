QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addpassagerdialog.cpp \
    addpassagerui.cpp \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    orderconfirmui.cpp \
    orderdetail.cpp \
    orderui.cpp \
    registerUi.cpp \
    switchorderdialog.cpp \
    ticketdetail.cpp \
    tickets.cpp \
    ticketsui.cpp \
    user.cpp \
    userui.cpp

HEADERS += \
    addpassager.Uicpp \
    addpassagerdialog.h \
    addpassagerui.h \
    client.h \
    mainwindow.h \
    orderconfirmui.h \
    orderdetail.h \
    orderui.h \
    registerUi.h \
    switchorderdialog.h \
    ticketdetail.h \
    tickets.h \
    ticketsui.h \
    user.h \
    userui.h

FORMS += \
    addpassagerdialog.ui \
    addpassagerui.ui \
    mainwindow.ui \
    orderconfirmui.ui \
    orderdetail.ui \
    orderui.ui \
    registerUi.ui \
    switchorderdialog.ui \
    ticketdetail.ui \
    ticketsui.ui \
    userui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    NewTicketClient.pro.user \
    main.ico \
    qss/silvery/add_bottom.png \
    qss/silvery/add_left.png \
    qss/silvery/add_right.png \
    qss/silvery/add_top.png \
    qss/silvery/branch_close.png \
    qss/silvery/branch_open.png \
    qss/silvery/calendar_nextmonth.png \
    qss/silvery/calendar_prevmonth.png \
    qss/silvery/checkbox_checked.png \
    qss/silvery/checkbox_checked_disable.png \
    qss/silvery/checkbox_parcial.png \
    qss/silvery/checkbox_parcial_disable.png \
    qss/silvery/checkbox_unchecked.png \
    qss/silvery/checkbox_unchecked_disable.png \
    qss/silvery/radiobutton_checked.png \
    qss/silvery/radiobutton_checked_disable.png \
    qss/silvery/radiobutton_unchecked.png \
    qss/silvery/radiobutton_unchecked_disable.png

RESOURCES += \
    resouce.qrc
