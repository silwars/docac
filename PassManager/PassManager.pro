QT       += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += console

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crypto.cpp \
    json.cpp \
    listcreds.cpp \
    main.cpp \
    mainwindow.cpp \
    modalwindow.cpp

HEADERS += \
    crypto.h \
    json.h \
    listcreds.h \
    mainwindow.h \
    modalwindow.h

FORMS += \
    listcreds.ui \
    mainwindow.ui \
    modalwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
include($$PWD/../Qt-Secret/src/Qt-Secret.pri)
