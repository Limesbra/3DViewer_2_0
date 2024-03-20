QT       += core gui opengl

macx {
    QT += openglwidgets
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl
greaterThan(QT_MAJOR_VERSION, 6):QT += openglwidgets

CONFIG += c++17
CONFIG += debug

# QMAKE_CXXFLAGS += -O3

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    view/mainwindow.cc \
    view/ogl_module.cc \
    view/app_settings.cc \
    model/data.cc \
    model/model.cc \
    model/parser.cc \
    external/gif.h


HEADERS += \
    view/mainwindow.h \
    view/ogl_module.h \
    view/app_settings.h \
    model/data.h \
    model/model.h \
    model/parser.h 

FORMS += \
    view/mainwindow.ui

UI_DIR = $$PWD/view

DESTDIR = $$PWD/../build

OBJECTS_DIR = $$PWD/objects


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
