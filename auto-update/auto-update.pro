TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ../headers/calendar.h

RC_ICONS = ../resources/icon.ico

unix:!macx: LIBS += -lgit2
