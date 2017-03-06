#include "chat.h"

Chat::Chat(QObject *parent): QObject(parent)
{
    m_qpChatFriendItemModel.reset(new ChatFriendItemModel(this));
}

ChatFriendItemModel* Chat::getChatFriendItemModel() const
{
    return m_qpChatFriendItemModel.data();
}

bool Chat::isChatWindowOpen()
{
    return !m_qpChatFriendItemModel->isEmpty();
}

void Chat::clearModel()
{
    if(!m_qpChatFriendItemModel->isEmpty())
    {
        QList<ChatFriendItem *> list = m_qpChatFriendItemModel->toList();
        m_qpChatFriendItemModel->clear();
        foreach (auto var, list)
        {
            delete var;
        }
    }
}

void Chat::setbSelected(QString friendAccount)
{
    QList<ChatFriendItem *> list = m_qpChatFriendItemModel->toList();
    foreach (auto var, list)
    {
        if(var->get_friendAccount() == friendAccount)
            var->set_bSelected(true);
        if(var->get_bSelected() && var->get_friendAccount() != friendAccount)
            var->set_bSelected(false);
    }
}

void Chat::loadDataToModel(QString friendName, QString friendAccount)
{
    QList<ChatFriendItem *> list = m_qpChatFriendItemModel->toList();
    foreach (auto var, list)
    {
        if(var->get_friendAccount() == friendAccount)
        {
            setbSelected(friendAccount);
            return;
        }
        if(var->get_bSelected())
            var->set_bSelected(false);
    }
    ChatFriendItem* item = new ChatFriendItem(this);
    item->set_friendName(friendName);
    item->set_friendAccount(friendAccount);
    item->set_bSelected(true);
    m_qpChatFriendItemModel->append(item);
}
