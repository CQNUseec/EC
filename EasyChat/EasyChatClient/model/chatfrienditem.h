#ifndef CHATFRIENDITEM_H
#define CHATFRIENDITEM_H

#include "QQmlObjectListModel.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlPtrPropertyHelpers.h"

class ChatFriendItem : public QObject         //聊天列表（正在聊天的好友列表）
{
    Q_OBJECT
    QML_WRITABLE_AUTO_PROPERTY(QString,     friendName)
    QML_WRITABLE_AUTO_PROPERTY(QString,     friendAccount)
    QML_WRITABLE_AUTO_PROPERTY(bool,        bSelected)
    //QML_WRITABLE_PTR_PROPERTY(QQmlObjectListModel<ChatFriendItem>,   chs)

    QML_OBJMODEL_PROPERTY(ChatFriendItem,               chs)
public:
    ChatFriendItem(QObject* parent) : QObject(parent),m_chs(new QQmlObjectListModel<ChatFriendItem>(this))
    {

    }
};

typedef QQmlObjectListModel<ChatFriendItem>  ChatFriendItemModel;
#endif // CHATFRIENDITEM_H
