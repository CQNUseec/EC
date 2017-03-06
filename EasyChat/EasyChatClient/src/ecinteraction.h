#ifndef ECINTERACTION_H
#define ECINTERACTION_H
#include "chat.h"
#include "friendlist.h"
#include "ecglobal.h"
#include <QSharedPointer>

class EcInteraction: public QObject      //UI接口类（提供所有的 UI和后台逻辑交互的 接口）
{
    Q_OBJECT
public:
    EcInteraction(QObject *parent);
    Q_INVOKABLE void      logIn(QString account, QString password);
//    Q_INVOKABLE void cancelLogin();
    Q_INVOKABLE QString   getSystemFont() const;
    FriendList*           getFriendList() const;
    Chat*                 getChat() const;
signals:
    void sig_loginResult(int res);
private:
    QSharedPointer<FriendList>    m_qpFriendList;
    QSharedPointer<Chat>          m_qpChat;
};

#endif // ECINTERACTION_H
