#-------------------------------------------------
#
# Project created by QtCreator 2019-09-12T17:14:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prS63BruteForceServer
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


SOURCES += \
        main.cpp \
        prS63BruteForceServer.cpp \
        TConnectionServer.cpp \
        TServerLogModel.cpp \
        TServerKeyModel.cpp \
        TClientDescr.cpp \
        ../../common/TException.cpp \
        ../../common/TConnection.cpp \
        ../../common/TDataModule.cpp

HEADERS += \
        prS63BruteForceServer.hpp \
        TConnectionServer.hpp \
        TServerLogModel.h \
        TServerKeyModel.h \
        TCommonDefineServer.hpp \
        ../../common/TCommonDefine.hpp \
        ../../common/TConnection.hpp \
        ../../common/TException.hpp \
        ../../common/TDataModule.h \
    TClientDescr.hpp

FORMS += \
        prS63BruteForceServer.ui

INCLUDEPATH += \
            ../../common

RESOURCES += \
        ../../res/resources.qrc
