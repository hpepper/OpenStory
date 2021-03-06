#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T16:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets help

TARGET = StoryTeller
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


SOURCES += \
    helpinformationdisplay.cpp \
        main.cpp \
        mainwindow.cpp \
    storagesave.cpp

HEADERS += \
    helpinformationdisplay.h \
        mainwindow.h \
    storagesave.h


# See: http://doc.qt.io/qtcreator/creator-project-qmake-libraries.html
unix|win32: LIBS += -ltinyxml2

## The help
## Using a "custom compiler"
#QHP_FILES += storyteller.qhp

#qhp_qhc.input = QHP_FILES
#qhp_qhc.output = ${QMAKE_FILE_BASE}.qch
#qhp_qhc.commands = qhelpgenerator ${QMAKE_FILE_NAME}
#qhp_qhc.CONFIG = no_link target_predeps
#QMAKE_EXTRA_COMPILERS += qhp_qhc

DISTFILES += \
    Docs/premise.html \
    Docs/storyteller.qhcp \
    Docs/storyteller.qhp \
    README.md \
    Notes.txt \
    TODO \
    docs/storyteller.qhcp \
    docs/storyteller.qhp \
    docs/premise.html \
    premise.html \
    storyteller.qhcp
