#ifndef CHAT_H
#define CHAT_H
#include <QSharedPointer>
#include "model/chatfrienditem.h"

class Chat: public QObject
{
    Q_OBJECT
public:
    Chat(QObject *parent);
    Q_PROPERTY(ChatFriendItemModel* getChatFriendItemModel READ getChatFriendItemModel CONSTANT)
    Q_INVOKABLE bool isChatWindowOpen();
    Q_INVOKABLE void clearModel();
    Q_INVOKABLE void setbSelected(QString friendAccount);
    Q_INVOKABLE void loadDataToModel(QString friendName, QString friendAccount);
    ChatFriendItemModel* getChatFriendItemModel() const;
private:
    QSharedPointer<ChatFriendItemModel>    m_qpChatFriendItemModel;
};

#endif // CHAT_H
