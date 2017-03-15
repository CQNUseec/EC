#include "messagelistmodel.h"

MessageListModel::MessageListModel(QString selfAccount, QObject *parent)
    : QAbstractListModel(parent), m_selfAccount(selfAccount)
{
    m_roleNames.insert(message, "message");
    m_roleNames.insert(sender, "sender");
    m_roleNames.insert(receiver, "receiver");
    m_roleNames.insert(sendTime, "sendTime");
    m_roleNames.insert(bDisplayLeft, "bDisplayLeft");
}

MessageListModel::~MessageListModel()
{
    clearModelData();
}

int MessageListModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    return m_qlMessage.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(m_qlMessage.isEmpty())
        return QVariant();
    switch (role) {
    case message:
        return m_qlMessage.at(index.row())->message;
    case sender:
        return m_qlMessage.at(index.row())->sender;
    case receiver:
        return m_qlMessage.at(index.row())->receiver;
    case sendTime:
        return m_qlMessage.at(index.row())->sendTime;
    case bDisplayLeft:
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

