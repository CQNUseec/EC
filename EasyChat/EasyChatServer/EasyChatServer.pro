QT += core sql
QT -= gui

CONFIG += c++11

TARGET = EasyChatServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    DB/account_terminal.cpp \
    DB/account.cpp \
    DB/group_linkman.cpp \
    DB/group.cpp \
    DB/linkman_linkmangroup.cpp \
    DB/linkmangroup.cpp \
    DB/offlinemessage.cpp \
    jsoncpp/json_reader.cpp \
    jsoncpp/json_value.cpp \
    jsoncpp/json_valueiterator.inl \
    jsoncpp/json_writer.cpp \
    DOMAIN/server.cpp \
    DOMAIN/chatcontrol.cpp \
    DB/dynamic.cpp \
    DB/commentary.cpp

HEADERS += \
    DB/account_terminal.h \
    DB/account.h \
    DB/group_linkman.h \
    DB/group.h \
    DB/linkman_linkmangroup.h \
    DB/linkmangroup.h \
    DB/offlinemessage.h \
    jsoncpp/allocator.h \
    jsoncpp/assertions.h \
    jsoncpp/autolink.h \
    jsoncpp/config.h \
    jsoncpp/features.h \
    jsoncpp/forwards.h \
    jsoncpp/json_tool.h \
    jsoncpp/json.h \
    jsoncpp/reader.h \
    jsoncpp/value.h \
    jsoncpp/version.h \
    jsoncpp/writer.h \
    DOMAIN/server.h \
    DOMAIN/chatcontrol.h \
    DB/dynamic.h \
    DB/commentary.h \
    DOMAIN/ecglobal.h
LIBS += -L/usr/local/lib -lboost_system
