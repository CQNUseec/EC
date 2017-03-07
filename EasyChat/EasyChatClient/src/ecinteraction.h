#ifndef ECINTERACTION_H
#define ECINTERACTION_H
#include "chat.h"
#include "friendlist.h"
#include "ecglobal.h"
#include <QSharedPointer>
class EcClient;
class EcInteraction: public QObject      //UI接口类（提供所有的 UI和后台逻辑交互的 接口）
{
    Q_OBJECT
public:
    explicit EcInteraction(QObject *parent);
    Q_PROPERTY(Chat* getChat READ getChat CONSTANT)
    Q_PROPERTY(FriendList* getFriendList READ getFriendList CONSTANT)
    Q_INVOKABLE void      sendMessage(QString jsonData);
    Q_INVOKABLE void      logIn(QString account, QString password);  //测试用 后续删除
    Q_INVOKABLE void      registerAccount(QString jsonData);         //测试用 后续删除
//    Q_INVOKABLE void cancelLogin();
    Q_INVOKABLE QString   getSystemFont() const;
    FriendList*           getFriendList() const;
    Chat*                 getChat() const;
    void                  parsingJsonData(QString jsonData);
signals:
    void sig_loginResult(int res);
    void sig_registerAccountResult(int error, QString account);
    void sig_sendMessage(QString jsonData);
private:
    QSharedPointer<FriendList>                     m_qpFriendList;
    QSharedPointer<Chat>                           m_qpChat;
};

#endif // ECINTERACTION_H
