#ifndef ECINTERACTION_H
#define ECINTERACTION_H
#include "chat.h"
#include "friendlist.h"
#include "ecglobal.h"
#include "model/groupmodel.h"
#include "model/mainmessagemodel.h"
#include <QSharedPointer>
class EcInteraction: public QObject      //UI接口类（提供所有的 UI和后台逻辑交互的 接口）
{
    Q_OBJECT
    Q_PROPERTY(Chat* chat READ getChat CONSTANT)
    // 群组列表的model
    Q_PROPERTY(GroupModel* chatGroupList READ chatGroupList CONSTANT)
    //主页消息列表的model
    // WRITE setmainMessageModel NOTIFY mainMessageModelChanged
    Q_PROPERTY(MainMessageModel* mainMessageModel READ mainMessageModel CONSTANT)
    Q_PROPERTY(FriendList* friendList READ getFriendList CONSTANT)
    Q_PROPERTY(QString selfAccount READ selfAccount WRITE setSelfAccount NOTIFY sig_selfAccountChanged)
public:
    explicit EcInteraction(QObject *parent);
    Q_INVOKABLE void      sendMessage(QString jsonData);
//    Q_INVOKABLE void cancelLogin();    
    Q_INVOKABLE void      closeClientThread(int i=1);   //默认参数为1   0代表不需要账号下线 直接关闭客户端
    Q_INVOKABLE QString   getRemarksName(QString friendAccount);
    Q_INVOKABLE void      setGroupSelected(QString GroupAccount);
    Q_INVOKABLE void      setSelfAccount(QString account);
    Q_INVOKABLE QString   getAccountName(QString account);
    Q_INVOKABLE void      removeMainMessageModelData(int idNum);
    Q_INVOKABLE bool      isGroupAccount(QString account);
    QString               selfAccount() const;
    FriendList*           getFriendList() const;
    GroupModel*           chatGroupList() const;
    MainMessageModel*     mainMessageModel() const;
    Chat*                 getChat() const; 
signals:
    void sig_loginResult(int res);
    void sig_registerAccountResult(QString account);
    void sig_findAccountResult(QString result, QString nickName="", QString age="", QString sex="");
    void sig_sendMessage(QString jsonData);
    void sig_selfAccountChanged(QString account);
    void sig_signOut(QString account);
    void sig_newMessage();
public slots:
    void slot_loadDataToChat(QStringList stringList);
private:
    QSharedPointer<FriendList>                     m_qpFriendList;
    QSharedPointer<GroupModel>                     m_qpGroupList;
    QSharedPointer<MainMessageModel>               m_mainMessageModel;
    QSharedPointer<Chat>                           m_qpChat;
    QString                                        m_selfAccount;
};

#endif // ECINTERACTION_H
