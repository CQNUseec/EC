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

void FriendList::loadDataToModel()
{
    FriendItem* rootItem = new FriendItem(this);
    rootItem->set_groupName("myFriends");
    auto children = rootItem->get_chs();
    for(int i=0;i<20;i++)
    {
        FriendItem* item = new FriendItem(rootItem);
        QString qsi = QString::number(i, 10);   //int型转换为QString类型   （int，进制）
        item->set_groupName(rootItem->get_groupName());
        item->set_account(qsi);
        item->set_nickName(QString("Friend ") + qsi);
        item->set_remarksName(QString("Friend备注") + qsi);
        item->set_bSelected(false);
        children->append(item);
    }
    m_qpFriendItemModel->append(rootItem);
    rootItem = new FriendItem(this);
    rootItem->set_groupName("classmates");
    auto Children = rootItem->get_chs();
    for(int i=0; i<40; i++)
    {
        FriendItem* item = new FriendItem(rootItem);
        QString qsi = QString::number(i+20, 10);
        item->set_groupName(rootItem->get_groupName());
        item->set_account(qsi);
        item->set_nickName(QString("classmate ") + qsi);
        item->set_remarksName(QString("classmate备注") + qsi);
        item->set_bSelected(false);
        Children->append(item);
    }
    m_qpFriendItemModel->append(rootItem);
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
                return mvar->get_remarksName();
        }
    }
    return "";
}
