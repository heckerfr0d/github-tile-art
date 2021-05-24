QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp

HEADERS += \
    headers/calendar.h \
    headers/font.h \
    headers/mainwindow.h

static { # everything below takes effect with CONFIG = static
    CONFIG+= static
    #CONFIG += staticlib # this is needed if you create a static library, not a static executable
    DEFINES+= STATIC
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# path to your built libgit2 library file
unix|win32: LIBS += -L$$PWD/../../libgit2-1.1.0/build/ -llibgit2.dll

# path to the libgit2 include folder
INCLUDEPATH += $$PWD/../../libgit2-1.1.0/include
DEPENDPATH += $$PWD/../../libgit2-1.1.0/include

RC_ICONS = resources/icon.ico
