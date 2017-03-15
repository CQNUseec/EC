#include "chatlistmodel.h"
ChatListModel::ChatListModel()
{
    m_roleNames.insert(friendAccountRole, "friendAccount");
    m_roleNames.insert(friendNameRole, "friendName");
    m_roleNames.insert(bSelectedRole, "bSelected");
    m_roleNames.insert(bUnreadMessageRole, "bUnreadMessage");
}

ChatListModel::~ChatListModel()
{
    clearModelData();
}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    return m_qlChatItemInfo.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(m_qlChatItemInfo.isEmpty())
        return QVariant();
    ChatItemInfo *temp = m_qlChatItemInfo.at(index.row());
    switch (role) {
    case friendAccountRole:
        return temp->friendAccount;
    case friendNameRole:
        return temp->friendName;
    case bSelectedRole:
        return temp->bSelected;
    case bUnreadMessageRole:
        return temp->bUnreadMessage;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatListModel::roleNames() const
{
    return m_roleNames;
}

void ChatListModel::loadDataToModel(QString friendAccount, QString friendName, bool bUnreadMessage)
{
    emit layoutAboutToBeChanged();
    bool isBreak = false;
    if(!m_qlChatItemInfo.isEmpty())
        foreach(auto var, m_qlChatItemInfo)
        {
            if(var->friendAccount == friendAccount)
            {
                var->bSelected = true;
                m_currentSelected = var->friendAccount;
                isBreak = true;
            }
            else
                var->bSelected = false;
        }
    if(isBreak)
    {
        emit layoutChanged();
        return;
    }
    ChatItemInfo* item = new ChatItemInfo;
    item->friendAccount = friendAccount;
    item->friendName = friendName;
    item->bUnreadMessage = bUnreadMessage;
    m_qlChatItemInfo.append(item);
    m_currentSelected = item->friendAccount;
    emit layoutChanged();
}

void ChatListModel::clearModelData()
{
    if(m_qlChatItemInfo.isEmpty())
        return;
    foreach(auto var, m_qlChatItemInfo)
        delete var;
    m_qlChatItemInfo.clear();
    m_currentSelected= "";
}

void ChatListModel::setBSelected(QString friendAccount)
{
    if(friendAccount == m_currentSelected)
        return;
    emit layoutAboutToBeChanged();
    foreach (auto var, m_qlChatItemInfo)
    {
        if(var->friendAccount == friendAccount)
        {
            var->bSelected = true;
            m_currentSelected = var->friendAccount;
        }
        else
            var->bSelected = false;
    }
    emit layoutChanged();
}

void ChatListModel::removeData(QModelIndex &index)
{
    int row = index.row();
}

bool ChatListModel::isEmpty()
{
    return m_qlChatItemInfo.isEmpty();
}
