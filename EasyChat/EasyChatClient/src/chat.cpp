#include "chat.h"

Chat::Chat(QObject *parent): QObject(parent)
{
    m_qpChatListModel.reset(new ChatListModel());
}

ChatListModel *Chat::chatListModel() const
{
    return m_qpChatListModel.data();
}

MessageListModel *Chat::messageListModel() const
{
    return m_qpCurrentMessageListModel;
}

void Chat::setMessageListModel(MessageListModel *currentMessageListModel)
{
    m_qpCurrentMessageListModel = currentMessageListModel;
    emit sig_messageListModelChanged(currentMessageListModel);
}

MessageListModel *Chat::getOneMessageListModel(QString account)
{
    for(auto it =m_qhMessageModel.begin(); it != m_qhMessageModel.end(); ++it)
    {
        if(it.key() == account)
            return it.value();
    }
    return nullptr;
}

bool Chat::isChatWindowOpen()
{
    return !m_qpChatListModel->isEmpty();
}

void Chat::clearChatData()
{
    m_qpChatListModel->clearModelData();
    m_qpCurrentMessageListModel = nullptr;
    for(auto it =m_qhMessageModel.begin(); it != m_qhMessageModel.end(); ++it)
    {
        it.value()->clearModelData();
        delete it.value();
    }
    m_qhMessageModel.clear();
}

void Chat::setCurrentChatPerson(QString friendAccount)
{
    m_qpChatListModel->setBSelected(friendAccount);
    auto ptr = getOneMessageListModel(friendAccount);
    setMessageListModel(ptr);
}

void Chat::loadDataToChat(QString friendName, QString friendAccount, QString selfAccount)
{
    m_qpChatListModel->loadDataToModel(friendAccount, friendName);
    auto ptr = getOneMessageListModel(friendAccount);
    if(ptr != nullptr)
        setMessageListModel(ptr);
    else
    {
        MessageListModel* messageListModel = new MessageListModel(selfAccount);
        m_qhMessageModel.insert(friendAccount, messageListModel);
    }
}

void Chat::loadDataToMessageListModel(QString sender, QString receiver, QString message, QString date)
{
    auto ptr = getOneMessageListModel(receiver);
    if(ptr == nullptr)
        return;
    ptr->loadDataToModel(sender, receiver, message, date);
}
