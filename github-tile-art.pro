QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp

HEADERS += \
    headers/calendar.h \
    headers/font.h \
    headers/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# path to libgit2.so and its include files
unix: LIBS += -L$$PWD/../libgit2-1.1.0/build/ -lgit2

INCLUDEPATH += $$PWD/../libgit2-1.1.0/include
DEPENDPATH += $$PWD/../libgit2-1.1.0/include
