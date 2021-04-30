QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp

HEADERS += \
    Headers/calendar.h \
    Headers/font.h \
    Headers/mainwindow.h

static { # everything below takes effect with CONFIG = static

CONFIG+= static
CONFIG += staticlib # this is needed if you create a static library, not a static executable
DEFINES+= STATIC
message("~~~ static build ~~~") # this is for information, that the static build is done
mac: TARGET = $$join(TARGET,,,_static) #this adds an _static in the end, so you can seperate static build

win32: TARGET = $$join(TARGET,,,s) #this adds an s in the end, so you can seperate static build from non static build

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Replace 'C:/Users/hadif/libgit2-1.1.0/build' with the path to built libgit2 library (libgit2.dll or libgit2.so)
# And     'C:/Users/hadif/libgit2-1.1.0/include' with the path to git2.h

unix|win32: LIBS += -LC:/Users/hadif/libgit2-1.1.0/build/ -llibgit2.dll

INCLUDEPATH += C:/Users/hadif/libgit2-1.1.0/build
INCLUDEPATH += C:/Users/hadif/libgit2-1.1.0/include
DEPENDPATH += C:/Users/hadif/libgit2-1.1.0/build

RESOURCES += \
    Resources/resources.qrc
