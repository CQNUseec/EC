TEMPLATE = app

QT += qml quick
CONFIG += c++11
QT += core sql

SOURCES += main.cpp \
    DB/account.cpp \
    DB/group.cpp \
    DB/group_linkman.cpp \
    DB/linkmangroup.cpp \
    DB/linkman_linkmangroup.cpp \
    DB/account_terminal.cpp \
    DB/offlinemessage.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    DB/account.h \
    DB/group.h \
    DB/group_linkman.h \
    DB/linkmangroup.h \
    DB/linkman_linkmangroup.h \
    DB/account_terminal.h \
    DB/offlinemessage.h
