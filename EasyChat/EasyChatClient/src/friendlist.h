#ifndef FRIENDLIST_H
#define FRIENDLIST_H
#include "model/frienditem.h"
#include <QObject>
#include <QSharedPointer>

class FriendList: public QObject             //好友列表
{
    Q_OBJECT
public:
    FriendList(QObject *parent);
    FriendItemModel* getFriendItemModel() const;
    void clearModel();
    void loadDataToModel();
    Q_INVOKABLE void setbSelected(QString groupName, QString friendAccount);
private:
    QSharedPointer<FriendItemModel>     m_qpFriendItemModel;
    QString     m_qsSelectedGroup{""};
    QString     m_qsSelectedFriendAccount{""};
    bool        m_isFirstSelected{true};
};

#endif // FRIENDLIST_H
