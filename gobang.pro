#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T13:39:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gobang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rolldice.cpp \
    game.cpp \
    player.cpp \
    welcome.cpp

HEADERS  += mainwindow.h \
    rolldice.h \
    game.h \
    player.h \
    welcome.h

FORMS    += mainwindow.ui \
    welcome.ui \
    rolldice.ui

RESOURCES += \
    image.qrc \
    dice.qrc
