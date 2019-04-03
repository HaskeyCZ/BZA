#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T19:56:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LFSRBZA
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    lfsr.cpp \
    qbitbutton.cpp \
    qlfsrcontroller.cpp \
    qlfsrxor.cpp \
    qsequenceoutput.cpp \
    qlfsroutputtable.cpp

HEADERS += \
        mainwindow.h \
    lfsr.h \
    qbitbutton.h \
    qlfsrcontroller.h \
    qlfsrxor.h \
    qsequenceoutput.h \
    qlfsroutputtable.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
