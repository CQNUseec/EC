#ifndef MYITEM_H
#define MYITEM_H


#include "QQmlObjectListModel.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlPtrPropertyHelpers.h"

class FriendItem : public QObject
{
    Q_OBJECT
    QML_WRITABLE_AUTO_PROPERTY(QString,     groupName)         //组名
    QML_WRITABLE_AUTO_PROPERTY(QString,     account)           //好友账号
    QML_WRITABLE_AUTO_PROPERTY(QString,     nickName)          // 好友昵称
    QML_WRITABLE_AUTO_PROPERTY(QString,     remarksName)       //好友备注名
    QML_WRITABLE_AUTO_PROPERTY(bool,        bSelected)
    //QML_WRITABLE_PTR_PROPERTY(QQmlObjectListModel<FriendItem>,   chs)

    QML_OBJMODEL_PROPERTY(FriendItem,               chs)
public:
    FriendItem(QObject* parent) : QObject(parent),m_chs(new QQmlObjectListModel<FriendItem>(this))
    {

    }
};
typedef QQmlObjectListModel<FriendItem>  FriendItemModel;

#endif // MYITEM_H
