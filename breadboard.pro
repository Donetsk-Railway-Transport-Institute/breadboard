#-------------------------------------------------
#
# Project created by QtCreator 2018-01-26T12:21:53
#
#-------------------------------------------------

QT       += core gui widgets script uitools
QT       += network serialport xmlpatterns
QT       += multimedia multimediawidgets

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = breadboard
TEMPLATE = app

#CONFIG += debug
CONFIG += release

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

#QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

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
    at_script_canvas.cpp \
    control_window.cpp \
    cyclocom.cpp \
    environment.cpp \
    general_window.cpp \
    main.cpp \
    objects_named_states.cpp \
    play_breadboard.cpp \
    rw_stantion.cpp \
    rw_view_obj.cpp \
    script_canvas.cpp \
    startup_config.cpp \
    before_started.cpp \
    camera.cpp

HEADERS += \
    at_script_canvas.h \
    control_window.h \
    cyclocom.h \
    environment.h \
    general_window.h \
    objects_named_states.h \
    play_breadboard.h \
    rw_stantion.h \
    rw_view_obj.h \
    script_canvas.h \
    startup_config.h \
    test_dcpp_viewer.h \
    views_obj.h \
    before_started.h \
    first_pix.h \
    camera.h \
    attcontroller.h

SUBDIRS += \
    breadboard.pro

DISTFILES += \
    breadboard.pro.user

CONFIG(debug, debug|release) {
    DESTDIR = $${PWD}/build/debug
    FILE_FROM = $${DESTDIR}/$${TARGET}.exe
    FILE_TO = $${PWD}/bin/debug/$${TARGET}.exe
}

CONFIG(release, debug|release) {
    DESTDIR = $${PWD}/build/release
    FILE_FROM = $${DESTDIR}/$${TARGET}.exe
    FILE_TO = $${PWD}/bin/release/$${TARGET}.exe
}

win32{
    DESTDIR ~= s,/,\\,g
    FILE_FROM ~= s,/,\\,g
    FILE_TO ~= s,/,\\,g
    QMAKE_POST_LINK += $$quote(cmd /c copy /y $${FILE_FROM} $${FILE_TO}$$escape_expand(\\n\\t))
}

#message("[INFO] cmd /c copy /y $${FILE_FROM} $${FILE_TO}")
#system(cmd /c copy /y $${FILE_FROM} $${FILE_TO}):HAS_BIN=FALSE


