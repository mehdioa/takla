#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T17:06:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x


TEMPLATE = app

MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build

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
    tkla.desktop \

unix:!macx { # installation on Unix-ish platforms
	isEmpty(INSTALL_PREFIX):INSTALL_PREFIX = /usr
	isEmpty(BIN_DIR):BIN_DIR = $$INSTALL_PREFIX/bin
	isEmpty(DATA_DIR):DATA_DIR = $$INSTALL_PREFIX/share
	isEmpty(ICON_DIR):ICON_DIR = $$DATA_DIR/pixmaps
	isEmpty(DESKTOP_DIR):DESKTOP_DIR = $$DATA_DIR/applications
#	isEmpty(TRANSLATIONS_DIR):TRANSLATIONS_DIR = $$DATA_DIR/takla/translations

	target.path = $$BIN_DIR
	icon.files = Images/takla.png
	icon.path = $$ICON_DIR
	desktop.files = takla.desktop
	desktop.path = $$DESKTOP_DIR
#	qm.files = translations/*.qm
#	qm.path = $$TRANSLATIONS_DIR

	INSTALLS = target icon desktop
}
