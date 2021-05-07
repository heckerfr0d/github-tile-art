TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../headers/calendar.h

win32: LIBS += -L$$PWD/../../../libgit2-1.1.0/build/ -llibgit2.dll

INCLUDEPATH += $$PWD/../../../libgit2-1.1.0/include
DEPENDPATH += $$PWD/../../../libgit2-1.1.0/include

RC_ICONS = ../resources/icon.ico
