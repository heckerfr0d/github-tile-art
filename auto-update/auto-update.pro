TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../headers/calendar.h

# path to libgit2.so and its include files
unix: LIBS += -L$$PWD/../../libgit2-1.1.0/build/ -lgit2

INCLUDEPATH += $$PWD/../../libgit2-1.1.0/include
DEPENDPATH += $$PWD/../../libgit2-1.1.0/include

