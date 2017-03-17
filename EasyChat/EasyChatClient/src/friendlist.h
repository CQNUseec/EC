#ifndef FRIENDLIST_H
#define FRIENDLIST_H
#include "model/frienditem.h"
#include <QObject>
#include <QSharedPointer>

class FriendList: public QObject             //好友列表的Model管理
{
    Q_OBJECT
public:
    FriendList(QObject *parent);
    Q_INVOKABLE void setbSelected(QString groupName, QString friendAccount);
    Q_INVOKABLE void setRemarksName(QString friendAccount, QString remarksName);
    Q_INVOKABLE bool setGroupName(QString oldName, QString newName);
    QString getRemarksName(QString friendAccount);
    FriendItemModel* getFriendItemModel() const;
    void clearModel();
    void loadDataToModel();
private:
    QSharedPointer<FriendItemModel>     m_qpFriendItemModel;
    QString     m_qsSelectedGroup{""};
    QString     m_qsSelectedFriendAccount{""};
    bool        m_isFirstSelected{true};
};

#endif // FRIENDLIST_H
