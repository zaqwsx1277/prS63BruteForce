#-------------------------------------------------
#
# Project created by QtCreator 2019-10-03T18:02:39
#
#-------------------------------------------------

QT       -= gui

TARGET = blowfish
TEMPLATE = lib

DEFINES += BLOWFISH_LIBRARY

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
        TBlowfish.cpp

HEADERS += \
        TBlowfish.hpp \
        blowfish_global.h  

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
