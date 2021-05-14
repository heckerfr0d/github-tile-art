TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../headers/calendar.h

# path to your built libgit2 library file
win32: LIBS += -L$$PWD/../../../libgit2-1.1.0/build/ -llibgit2.dll

# path to the libgit2 include folder
INCLUDEPATH += $$PWD/../../../libgit2-1.1.0/include
DEPENDPATH += $$PWD/../../../libgit2-1.1.0/include

RC_ICONS = ../resources/icon.ico
