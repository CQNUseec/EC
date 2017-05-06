#include "friendlist.h"

FriendList::FriendList(QObject *parent): QObject(parent)
{
    m_qpFriendItemModel.reset(new FriendItemModel(this));
}

FriendItemModel *FriendList::getFriendItemModel() const
{
    return m_qpFriendItemModel.data();
}

void FriendList::clearModel()
{
    if(m_qpFriendItemModel->count() > 0)
    {
        QList<FriendItem *> list = m_qpFriendItemModel->toList();
        m_qpFriendItemModel->clear();
        foreach (auto var, list)
        {
            delete var;
        }
    }
}

void FriendList::loadDataToModel(QString groupName, QString account, QString nickName,
                                 QString remarkName)
{
    FriendItem* item;
    if(m_qpFriendItemModel->count() > 0)
    {
        QList<FriendItem *> list = m_qpFriendItemModel->toList();
        foreach(auto var, list)
        {
            if(var->get_groupName() == groupName)
            {
                item = new FriendItem(var);
                item->set_groupName(groupName);
                item->set_account(account);
                item->set_nickName(nickName);
                item->set_remarksName(remarkName);
                item->set_bSelected(false);
                var->get_chs()->append(item);
                return;
            }
        }
    }
    FriendItem* rootItem = new FriendItem(this);
    rootItem->set_groupName(groupName);
    m_qpFriendItemModel->append(rootItem);
    item = new FriendItem(rootItem);
    item->set_groupName(groupName);
    item->set_account(account);
    item->set_nickName(nickName);
    item->set_remarksName(remarkName);
    rootItem->get_chs()->append(item);
    item->set_bSelected(false);
    return;
}

void FriendList::slot_loadDataToFriendList(QStringList stringList)
{
    loadDataToModel(stringList.at(0), stringList.at(1),
                    stringList.at(2), stringList.at(3));
}

void FriendList::setbSelected(QString groupName, QString friendAccount)
{
    if(m_qsSelectedGroup == groupName && m_qsSelectedFriendAccount == friendAccount)
        return;
    QList<FriendItem *> list = m_qpFriendItemModel->toList();
    if(!m_isFirstSelected)
    {
        foreach (auto var, list)
        {
            if(var->get_groupName() == m_qsSelectedGroup)
            {
                QList<FriendItem *> groupMemberList = var->get_chs()->toList();
                foreach (auto mvar, groupMemberList)
                {
                    if(mvar->get_account() == m_qsSelectedFriendAccount)
                    {
                        mvar->set_bSelected(false);
                        break;
                    }
                }
                break;
            }
        }
    }
    foreach (auto var, list)
    {
        if(var->get_groupName() == groupName)
        {
            QList<FriendItem *> groupMemberList = var->get_chs()->toList();
            foreach (auto mvar, groupMemberList)
            {
                if(mvar->get_account() == friendAccount)
                {
                    mvar->set_bSelected(true);
                    m_isFirstSelected = false;
                    m_qsSelectedGroup = mvar->get_groupName();
                    m_qsSelectedFriendAccount = mvar->get_account();
                    return;
                }
            }
        }
    }
}

void FriendList::setRemarksName(QString friendAccount, QString remarksName)
{
    QList<FriendItem *> list = m_qpFriendItemModel->toList();
    foreach(auto var, list)
    {
        QList<FriendItem *> groupMemberList = var->get_chs()->toList();
        foreach(auto mvar, groupMemberList)
        {
            if(mvar->get_account() == friendAccount)
                mvar->set_remarksName(remarksName);
        }
    }
}

bool FriendList::setGroupName(QString oldName, QString newName)
{
    QList<FriendItem *> list = m_qpFriendItemModel->toList();
    foreach (auto var, list)
    {
        if(var->get_groupName() == newName)
            return false;
    }
    foreach(auto var, list)
    {
        if(var->get_groupName() == oldName)
        {
            var->set_groupName(newName);
            QList<FriendItem *> groupMemberList = var->get_chs()->toList();
            foreach(auto mvar, groupMemberList)
            {
                mvar->set_groupName(newName);
            }
            return true;
        }
    }
}

QString FriendList::getRemarksName(QString friendAccount)
{
    QList<FriendItem *> list = m_qpFriendItemModel->toList();
    foreach(auto var, list)
    {
        QList<FriendItem *> groupMemberList = var->get_chs()->toList();
        foreach(auto mvar, groupMemberList)
        {
            if(mvar->get_account() == friendAccount)
               if(mvar->get_remarksName().isEmpty())
                   return mvar->get_nickName();
               else
                return mvar->get_remarksName();
        }
    }
    return "";
}
