TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../headers/calendar.h

ICON = ../resources/github-tile-art.icns

macx: LIBS += -L$$PWD/../../Downloads/libgit2-1.1.0/build/ -lgit2.1.1.0

INCLUDEPATH += $$PWD/../../Downloads/libgit2-1.1.0/include
DEPENDPATH += $$PWD/../../Downloads/libgit2-1.1.0/include
