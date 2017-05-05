TEMPLATE = app
QT += widgets multimedia qml quick
CONFIG += c++14

SOURCES += \
    src/chat.cpp \
    src/ecinteraction.cpp \
    src/friendlist.cpp \
    src/main.cpp \
    src/ecclient.cpp \
    src/ecclientthread.cpp \
    model/chatlistmodel.cpp \
    model/messagelistmodel.cpp \
    src/singleApplication.cpp \
    model/groupmodel.cpp \
    model/mainmessagemodel.cpp \
    src/network.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model/frienditem.h \
    model/QQmlAutoPropertyHelpers.h \
    model/QQmlHelpersCommon.h \
    model/QQmlObjectListModel.h \
    model/QQmlPtrPropertyHelpers.h \
    src/chat.h \
    src/ecinteraction.h \
    src/friendlist.h \
    src/ecglobal.h \
    src/ecclient.h \
    src/ecclientthread.h \
    model/chatlistmodel.h \
    model/messagelistmodel.h \
    src/singleApplication.h \
    model/groupmodel.h \
    model/mainmessagemodel.h \
    src/network.h

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/lib/libboost_system.a
