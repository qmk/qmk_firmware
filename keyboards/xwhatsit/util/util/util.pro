# Copyright 2020 Purdea Andrei
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#-------------------------------------------------
#
# Project created by QtCreator 2020-05-02T21:08:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = util
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    monitorwindow.cpp \
    communication.cpp \
    device.cpp \
    hidthread.cpp \
    kbd_defs.cpp \
    signal_level.cpp \
    columntester.cpp \
    rowdactester.cpp

HEADERS += \
        mainwindow.h \
    monitorwindow.h \
    communication.h \
    device.h \
    hidthread.h \
    kbd_defs.h \
    signal_level.h \
    columntester.h \
    rowdactester.h

unix:!macx {
    LIBS += -lhidapi-libusb
    #LIBS += -lhidapi-hidraw
    INCLUDEPATH += /usr/include/hidapi
}

macx {
    INCLUDEPATH += /usr/local/opt/hidapi/include/hidapi
    LIBS += -L/usr/local/opt/hidapi/lib -lhidapi
}

win32 {
    # Note: at the moment this configuration is for cross-compiling only. I have not tested native windows compilation.
    INCLUDEPATH += /mxe/usr/i686-w64-mingw32.static/include/hidapi
    LIBS += -lhidapi -lsetupapi
}

FORMS += \
        mainwindow.ui \
    monitorwindow.ui \
    signal_level.ui \
    columntester.ui \
    rowdactester.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
