#include "groupmodel.h"

GroupModel::GroupModel(QString selfAccount) : m_selfAccount(selfAccount)
{
    m_roleNames.insert(groupAccoutRole, "groupAccount");
    m_roleNames.insert(groupNameRole, "groupName");
    m_roleNames.insert(bSelectedRole, "bSelected");
    QStringList sq("1");
    loadDataToModel("12154545", "group1", " ", sq);
    loadDataToModel("12154245", "group2", " ", sq);
    loadDataToModel("12124545", "group3", " ", sq);
}

GroupModel::~GroupModel()
{
    clearModelData();
}

int GroupModel::rowCount(const QModelIndex &parent) const
{
    return m_qlGroupItemInfo.count();
}

QVariant GroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(m_qlGroupItemInfo.isEmpty())
        return QVariant();
    switch (role)
    {
    case groupAccoutRole:
        return m_qlGroupItemInfo.at(index.row())->groupAccount;
    case groupNameRole:
        return m_qlGroupItemInfo.at(index.row())->groupName;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GroupModel::roleNames() const
{
    return m_roleNames;
}

void GroupModel::loadDataToModel(QString groupAccount, QString groupName, QString groupOwner, QStringList groupMember)
{
    if(groupAccount.isEmpty() || groupName.isEmpty() || groupMember.isEmpty() || groupOwner.isEmpty())
        return;
    emit layoutAboutToBeChanged();
    GroupItemInfo* groupItemPtr = new GroupItemInfo;
    groupItemPtr->groupAccount = groupAccount;
    groupItemPtr->groupName = groupName;
    groupItemPtr->groupOwner = groupOwner;
    m_qlGroupItemInfo.append(groupItemPtr);
    m_qhGroupMember.insert(groupAccount, groupMember);
    emit layoutChanged();
}

void GroupModel::setSelfAccount(QString selfAccount)
{
    m_selfAccount = selfAccount;
}

void GroupModel::setbSelected(QString groupAccout)
{
    emit layoutAboutToBeChanged();
    foreach (auto var, m_qlGroupItemInfo)
    {
        if(var->groupAccount == groupAccout && var->bSelected)
            return;
        else if(var->bSelected)
            var->bSelected = false;
    }
    foreach (auto var, m_qlGroupItemInfo)
    {
        if(var->groupAccount == groupAccout)
            var->bSelected = true;
    }
    emit layoutChanged();
}

void GroupModel::clearModelData()
{
    m_qhGroupMember.clear();
    if(m_qlGroupItemInfo.isEmpty())
        return;
    foreach (auto var, m_qlGroupItemInfo)
    {
        delete var;
    }
    m_qlGroupItemInfo.clear();
}
