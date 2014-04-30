#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T17:06:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11


TARGET = kla
TEMPLATE = app


SOURCES += Source/main.cpp \
        Source/mainwindow.cpp \
        Source/percentagewindow.cpp \
    Source/comparedialog.cpp \
    Source/keyboard.cpp \
    Source/keyboardconstants.cpp


HEADERS  += Source/mainwindow.h \
        Source/percentagewindow.h \
    Source/comparedialog.h \
    Source/keyboard.h \
    Source/keyboardconstants.h


FORMS    += Source/mainwindow.ui \
    Source/percentagewindow.ui \
    Source/comparedialog.ui \


RESOURCES += \
    Images.qrc

OTHER_FILES += \
    kla.desktop \

