#include "messagelistmodel.h"

MessageListModel::MessageListModel(QString selfAccount)
    : m_selfAccount(selfAccount)
{
    m_roleNames.insert(messageRole, "message");
    m_roleNames.insert(senderRole, "sender");
    m_roleNames.insert(receiverRole, "receiver");
    m_roleNames.insert(sendTimeRole, "sendTime");
    m_roleNames.insert(bDisplayLeftRole, "bDisplayLeft");
}

MessageListModel::~MessageListModel()
{
    clearModelData();
}

int MessageListModel::rowCount(const QModelIndex &parent) const
{
//    if (!parent.isValid())
//        return 0;
    return m_qlMessage.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(m_qlMessage.isEmpty())
        return QVariant();
    switch (role) {
    case messageRole:
        return m_qlMessage.at(index.row())->message;
    case senderRole:
        return m_qlMessage.at(index.row())->sender;
    case receiverRole:
        return m_qlMessage.at(index.row())->receiver;
    case sendTimeRole:
        return m_qlMessage.at(index.row())->sendTime;
    case bDisplayLeftRole:
        return m_qlMessage.at(index.row())->bDisplayLeft;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MessageListModel::roleNames() const
{
    return m_roleNames;
}

void MessageListModel::loadDataToModel(QString sender, QString receiver, QString message, QString sendTime)
{
    emit layoutAboutToBeChanged();
    Message* messagePtr = new Message;
    messagePtr->message = message;
    messagePtr->sender = sender;
    messagePtr->receiver = receiver;
    messagePtr->sendTime = sendTime;
    if(sender == m_selfAccount)
        messagePtr->bDisplayLeft = false;
    m_qlMessage.append(messagePtr);
    emit layoutChanged();
}

void MessageListModel::clearModelData()
{
    if(m_qlMessage.isEmpty())
        return;
    foreach (auto var, m_qlMessage)
    {
        delete var;
    }
    m_qlMessage.clear();
}

