#ifndef ECINTERACTION_H
#define ECINTERACTION_H
#include "chat.h"
#include "friendlist.h"
#include "ecglobal.h"
#include "model/groupmodel.h"
#include <QSharedPointer>
class EcInteraction: public QObject      //UI接口类（提供所有的 UI和后台逻辑交互的 接口）
{
    Q_OBJECT
    Q_PROPERTY(Chat* chat READ getChat CONSTANT)
    // 群组列表的model
    Q_PROPERTY(GroupModel* chatGroupList READ chatGroupList CONSTANT)
    Q_PROPERTY(FriendList* friendList READ getFriendList CONSTANT)
    Q_PROPERTY(QString selfAccount READ selfAccount WRITE setSelfAccount NOTIFY sig_selfAccountChanged)
public:
    explicit EcInteraction(QObject *parent);
    Q_INVOKABLE void      sendMessage(QString jsonData);
//    Q_INVOKABLE void cancelLogin();
    Q_INVOKABLE void      setSelfAccount(QString account);
    Q_INVOKABLE void      closeClientThread();
    Q_INVOKABLE QString   getRemarksName(QString friendAccount);
    Q_INVOKABLE void      setGroupSelected(QString GroupAccount);
    QString               selfAccount() const;
    FriendList*           getFriendList() const;
    GroupModel*           chatGroupList() const;
    Chat*                 getChat() const;
signals:
    void sig_loginResult(int res);
    void sig_registerAccountResult(int error, QString account);
    void sig_sendMessage(QString jsonData);
    void sig_selfAccountChanged(QString account);
    void sig_signOut(QString account);
private:
    QSharedPointer<FriendList>                     m_qpFriendList;
    QSharedPointer<GroupModel>                     m_qpGroupList;
    QSharedPointer<Chat>                           m_qpChat;
    QString                                        m_selfAccount;
};

#endif // ECINTERACTION_H
