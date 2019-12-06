#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T13:35:24
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperDT
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
    Widget/StatusBar.cpp \
    Widget/TitleBar.cpp \
    main.cpp \
    MainWidget.cpp \
    Widget/TMsgArea.cpp \
    Widget/TTextEditor.cpp \
    Widget/TSettingArea.cpp \
    Form/TCard.cpp \
    Form/TButton.cpp \
    Form/TCardItem.cpp \
    Form/TComBox.cpp \
#    General/Network/AbsConnection.cpp \
#    General/Network/CConnectionForClient.cpp \
#    General/Network/CConnectionForServer.cpp \
#    General/Network/CConnectionForUdp.cpp \
#    General/Network/CNetworkForClients.cpp \
#    General/Network/CNetworkForServer.cpp \
#    General/Network/CNetworkForUdps.cpp \
    Application/NetworkApp.cpp \
    Form/TCardUserItem.cpp \
    General/Log/CLogWin.cpp \
    General/Log/CLogWinForWindow.cpp \
    General/Log/CLogWinForDB.cpp \
    General/Log/CLogWinForTxt.cpp \
    General/Log/CLogWinEnm.cpp \
    Widget/TSettingBtnBar.cpp \
    Form/TLockButton.cpp


HEADERS += \
    MainWidget.h \
    Widget/StatusBar.h \
    Widget/TWindowLayoutDefine.h \
    Widget/TitleBar.h \
    Widget/TMsgArea.h \
    Widget/TTextEditor.h \
    Widget/TSettingArea.h \
    Form/TCard.h \
    Form/TButton.h \
    Form/TCardItem.h \
    Form/TComBox.h \
#    General/Network/AbsConnection.h \
#    General/Network/CConnectionForClient.h \
#    General/Network/CConnectionForServer.h \
#    General/Network/CConnectionForUdp.h \
#    General/Network/CNetworkForClients.h \
#    General/Network/CNetworkForServer.h \
#    General/Network/CNetworkForUdps.h \
#    General/Network/INetworkInterface.h \
    General/Log/clog.h \
    General/Log/CLogWin.h \
    Application/NetworkApp.h \
    Form/TCardUserItem.h \
    General/Log/CLogWin.h \
    General/Log/CLogWinForWindow.h \
    General/Log/CLogWinForDB.h \
    General/Log/CLogWinForTxt.h \
    General/Log/CLogWinEnm.h \
    Widget/TSettingBtnBar.h \
    Form/TLockButton.h

INCLUDEPATH += \
        Widget \
        Form \
        General/Log \
        General/Network \
        General/Database \
        Application \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagerc.qrc

RC_FILE += icon.rc

DISTFILES += \
    General/Log/LogWinConfig.xml

