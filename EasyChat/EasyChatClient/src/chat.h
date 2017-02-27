#ifndef CHAT_H
#define CHAT_H
#include <QSharedPointer>
#include "model/chatfrienditem.h"

class Chat: public QObject
{
    Q_OBJECT
public:
    Chat(QObject *parent);
    ChatFriendItemModel* getChatFriendItemModel() const;
    Q_INVOKABLE bool isChatWindowOpen();
    Q_INVOKABLE void clearModel();
    Q_INVOKABLE void setbSelected(QString friendAccount);
    Q_INVOKABLE void loadDataToModel(QString friendName, QString friendAccount);
private:
    QSharedPointer<ChatFriendItemModel>    m_qpChatFriendItemModel;
};

#endif // CHAT_H
