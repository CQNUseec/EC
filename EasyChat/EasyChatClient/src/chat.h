#ifndef CHAT_H
#define CHAT_H
#include <QSharedPointer>
#include "model/chatlistmodel.h"
#include "model/messagelistmodel.h"

class Chat: public QObject             //处理聊天界面的相关逻辑
{
    Q_OBJECT
    //正在聊天的好友列表model
    Q_PROPERTY(ChatListModel* chatListModel READ chatListModel CONSTANT)
    //聊天窗口聊天信息显示的medel
    Q_PROPERTY(MessageListModel* messageListModel READ messageListModel WRITE setMessageListModel NOTIFY sig_messageListModelChanged)
public:
    Chat(QObject *parent);
    ~Chat();
    Q_INVOKABLE bool isChatWindowOpen();
    //清除所有数据
    Q_INVOKABLE void clearChatData();
    Q_INVOKABLE void setCurrentChatPerson(QString friendAccount);
    //设置聊天窗口当前聊天的对象
    Q_INVOKABLE void loadDataToChat(QString friendName, QString friendAccount, QString selfAccount);
    Q_INVOKABLE void removeDataFromChat(QString friendAccount);
    Q_INVOKABLE void loadDataToMessageListModel(QString sender, QString receiver, QString message, QString date);
//    Q_INVOKABLE void removeChataData(QString friendAccount);
    ChatListModel* chatListModel() const;
    MessageListModel* messageListModel() const;
signals:
    void sig_messageListModelChanged(MessageListModel* currentMessageListModel);
    void sig_viewChanged(int count=1);
private:
    void setMessageListModel(MessageListModel* currentMessageListModel);
    MessageListModel* getOneMessageListModel(QString account);
private:
    QSharedPointer<ChatListModel>       m_qpChatListModel;                         //正在聊天的好友列表model
    QHash<QString, MessageListModel*>   m_qhMessageModel;                          //聊天窗口聊天信息显示的medel表， 一个聊天对象账号对应一个model
    MessageListModel*                   m_qpCurrentMessageListModel{nullptr};      //当前的显示的聊天消息model
};

#endif // CHAT_H
