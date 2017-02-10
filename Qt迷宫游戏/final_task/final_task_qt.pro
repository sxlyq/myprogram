#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T16:12:04
#
#-------------------------------------------------

CONFIG += c++14

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = final_task_qt
TEMPLATE = app


SOURCES += main.cpp\
    pathfinder.cpp \
    plannernode.cpp\
    location.cpp \
    mainwindow.cpp \
    game.cpp \


HEADERS  += \
    ../libworld.so/world.h \
    ../libworld.so/world_global.h \
    pathfinder.h \
    plannernode.h \
    location.h \
    direction.h \
    mainwindow.h \
    game.h \


FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libworld.so/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libworld.so/debug/ -lworld
else:unix: LIBS += -L$$PWD/../libworld.so/ -lworld

INCLUDEPATH += $$PWD/../libworld.so
DEPENDPATH += $$PWD/../libworld.so

RESOURCES += \
    images.qrc

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../medproc/libworld.so/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../medproc/libworld.so/debug/ -lworld
else:unix: LIBS += -L$$PWD/../medproc/libworld.so/ -lworld

INCLUDEPATH += $$PWD/../medproc/libworld.so
DEPENDPATH += $$PWD/../medproc/libworld.so

unix|win32: LIBS += -L$$PWD/../libworld.so/ -lworld

INCLUDEPATH += $$PWD/../libworld.so
DEPENDPATH += $$PWD/../libworld.so
