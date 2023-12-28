QT       += core gui sql

TARGET = DataBase
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Coach.cpp \
    People.cpp \
    Player.cpp \
    RenewContract.cpp \
    dbmanager.cpp \
    deletecoach.cpp \
    deletecoachfromtable.cpp \
    deleteplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    photomodel.cpp \
    renewcoachcontract.cpp \
    signin.cpp \
    signup.cpp \
    sqlmanager.cpp \
    startwindow.cpp \
    updateallcoach.cpp \
    updateallplayer.cpp

HEADERS += \
    Coach.h \
    People.h \
    Player.h \
    RenewContract.h \
    dbmanager.h \
    deletecoach.h \
    deletecoachfromtable.h \
    deleteplayer.h \
    mainwindow.h \
    photomodel.h \
    renewcoachcontract.h \
    signin.h \
    signup.h \
    sqlmanager.h \
    startwindow.h \
    updateallcoach.h \
    updateallplayer.h

FORMS += \
    RenewContract.ui \
    deletecoach.ui \
    deletecoachfromtable.ui \
    deleteplayer.ui \
    mainwindow.ui \
    renewcoachcontract.ui \
    signin.ui \
    signup.ui \
    startwindow.ui \
    updateallcoach.ui \
    updateallplayer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# Share all project output files by directories
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui
unix:OBJECTS_DIR = unix
win32:OBJECTS_DIR = win32
macx:OBJECTS_DIR = mac

# If release-buid -> run windeploy applications, that will collect all the dlls
CONFIG(release, debug|release) {
    win32:QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/release
}

RESOURCES += \
    resurs.qrc
