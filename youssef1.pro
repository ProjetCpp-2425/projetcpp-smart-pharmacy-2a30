QT       += core gui sql widgets
QT += charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addemployee.cpp \
    connection.cpp \
    editemployee.cpp \
    employee.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    addemployee.h \
    connection.h \
    editemployee.h \
    employee.h \
    login.h \
    mainwindow.h

FORMS += \
    addemployee.ui \
    editemployee.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/img.qrc

DISTFILES += \
    Resources/School.db \
    Resources/img/add.png \
    Resources/img/delete.png \
    Resources/img/excel.png \
    Resources/img/font.png \
    Resources/img/ok.png \
    Resources/img/password.png \
    Resources/img/print.png \
    Resources/img/printer.png \
    Resources/img/reload.png \
    Resources/img/search.png \
    Resources/img/select.png \
    Resources/img/settings.png \
    Resources/img/sorting.png \
    Resources/img/support.png \
    Resources/img/teacgers.png
