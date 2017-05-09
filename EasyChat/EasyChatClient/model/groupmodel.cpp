#include "groupmodel.h"

GroupModel::GroupModel(QString selfAccount) : m_selfAccount(selfAccount)
{
    m_roleNames.insert(groupAccoutRole, "groupAccount");
    m_roleNames.insert(groupNameRole, "groupName");
    m_roleNames.insert(bSelectedRole, "bSelected");
//    QStringList sq("1");
//    loadDataToModel("123", "group1", " ");
//    loadDataToModel("124", "group2", " ", sq);
//    loadDataToModel("125", "group3", " ", sq);
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
    case bSelectedRole:
        return m_qlGroupItemInfo.at(index.row())->bSelected;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GroupModel::roleNames() const
{
    return m_roleNames;
}

void GroupModel::loadDataToModel(QString groupAccount, QString groupName, QString groupOwner)
{
    if(groupAccount.isEmpty() || groupName.isEmpty() || groupOwner.isEmpty())
        return;
    emit layoutAboutToBeChanged();
    GroupItemInfo* groupItemPtr = new GroupItemInfo;
    groupItemPtr->groupAccount = groupAccount;
    groupItemPtr->groupName = groupName;
    groupItemPtr->groupOwner = groupOwner;
    m_qlGroupItemInfo.append(groupItemPtr);
    emit layoutChanged();
    emit sig_flushUI();
}

void GroupModel::loadGroupMemberInfo(QString gAccount, QString mAccount, QString mNickName, QString mAge, QString mSex)
{
    for(auto it=m_qhGroupMember.begin(); it != m_qhGroupMember.end(); ++it)
    {
        if(it.key() == gAccount)
        {
            GroupMemberInfo *mInfo = new GroupMemberInfo;
            mInfo->mAccount = mAccount;
            mInfo->mNickName = mNickName;
            mInfo->mAge = mAge;
            mInfo->mSex = mSex;
            it.value()->append(mInfo);
            return;
        }
    }
    GroupMemberInfo *mInfo = new GroupMemberInfo;
    mInfo->mAccount = mAccount;
    mInfo->mNickName = mNickName;
    mInfo->mAge = mAge;
    mInfo->mSex = mSex;
    QList<GroupMemberInfo*>* qmlist = new QList<GroupMemberInfo *>;
    qmlist->append(mInfo);
    m_qhGroupMember.insert(gAccount, qmlist);
    return;
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

bool GroupModel::isGroupAccount(QString account)
{
    foreach (auto var, m_qlGroupItemInfo)
    {
        if(var->groupAccount == account)
            return true;
    }
    return false;
}

QString GroupModel::getMemberName(QString account)
{
    for(auto it=m_qhGroupMember.begin(); it != m_qhGroupMember.end(); ++it)
    {
        foreach(auto &var, *(it.value()))
        {
            if(var->mAccount == account)
                return var->mNickName;
        }
    }
}

void GroupModel::clearModelData()
{
    for(auto it=m_qhGroupMember.begin(); it != m_qhGroupMember.end(); ++it)
    {
        foreach(auto &var, *(it.value()))
        {
            delete var;
        }
        it.value()->clear();
        delete it.value();
    }
    m_qhGroupMember.clear();
    if(m_qlGroupItemInfo.isEmpty())
        return;
    foreach (auto &var, m_qlGroupItemInfo)
    {
        delete var;
    }
    m_qlGroupItemInfo.clear();
}
