#include "chat.h"

Chat::Chat(QObject *parent): QObject(parent)
{
    m_qpChatListModel.reset(new ChatListModel());
}

Chat::~Chat()
{
    clearChatData();
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

bool Chat::isChatToSender(QString senderAccount)
{
    return m_qpChatListModel->isAccountExist(senderAccount);
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
    if(m_qpChatListModel->isAccountExist(friendAccount))
        ;
    else
        m_qpChatListModel->loadDataToModel(friendAccount, friendName, friendName);
    auto ptr = getOneMessageListModel(friendAccount);
    if(ptr != nullptr)
        setMessageListModel(ptr);
    else
    {
        MessageListModel* messageListModel = new MessageListModel(selfAccount);
        m_qhMessageModel.insert(friendAccount, messageListModel);
        for(auto it=m_tempChatData.begin(); it != m_tempChatData.end(); )
        {
            if((*it)->sender == friendAccount)
            {
                messageListModel->loadDataToModel((*it)->sender, (*it)->receiver, (*it)->message, (*it)->sendTime);
                delete *it;
                it = m_tempChatData.erase(it);
            }
            else
                ++it;
        }
        setMessageListModel(messageListModel);
    }
}

void Chat::removeDataFromChat(QString friendAccount)
{
    QString temp = m_qpChatListModel->removeData(friendAccount);
    delete getOneMessageListModel(friendAccount);
    m_qhMessageModel.remove(friendAccount);
    if(temp != "")
    {
        setMessageListModel(getOneMessageListModel(temp));
    }
    else
    {
        clearChatData();
    }
    emit sig_viewChanged(m_qhMessageModel.count());
}

void Chat::loadDataToMessageListModel(QString sender, QString receiver, QString message, QString date)
{
    if(m_qpCurrentMessageListModel == nullptr)
        return;
    m_qpCurrentMessageListModel->loadDataToModel(sender, receiver, message, date);
    emit sig_viewChanged();
}

void Chat::loadDataToTemp(QString sender, QString receiver, QString message, QString date)
{
    MessageListModel::Message* item = new MessageListModel::Message;
    item->sender = sender;
    item->receiver = receiver;
    item->message = message;
    item->sendTime = date;
    m_tempChatData.append(item);
}
