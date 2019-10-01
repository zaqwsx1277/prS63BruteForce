#-------------------------------------------------
#
# Project created by QtCreator 2019-09-30T17:44:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testDecrypt
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
        prTestDecrypt.cpp \
    TTestDecryptLogModel.cpp

HEADERS += \
        prTestDecrypt.hpp \
    TTestDecryptLogModel.hpp \
    TTestDecryptCommon.hpp

FORMS += \
        prTestDecrypt.ui

## Unix Правила линковки библиотек Botan
unix:!macx: INCLUDEPATH += /usr/include/botan-2
unix:!macx: LIBS += -L/usr/include -lbotan-2

# подключаем zlib
unix:!macx: LIBS += -lz


## Windows Правила линковки библиотек Botan
win32: LIBS += -L$$PWD/winDll/botan/binDebug/ -lbotan

win32: INCLUDEPATH += winDll/botan/include
win32: DEPENDPATH += winDll/botan/include

# подключаем zlib
win32: LIBS += -L$$PWD/winDll/zlib/ -lzlib

win32: INCLUDEPATH += winDll/zlib
