TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += \
    src/chat.cpp \
    src/ecinteraction.cpp \
    src/friendlist.cpp \
    src/main.cpp \
    src/ecclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model/chatfrienditem.h \
    model/frienditem.h \
    model/QQmlAutoPropertyHelpers.h \
    model/QQmlHelpersCommon.h \
    model/QQmlObjectListModel.h \
    model/QQmlPtrPropertyHelpers.h \
    src/chat.h \
    src/ecinteraction.h \
    src/friendlist.h \
    src/ecglobal.h \
    src/ecclient.h
