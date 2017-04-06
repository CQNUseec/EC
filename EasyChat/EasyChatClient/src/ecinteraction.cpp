#include "ecinteraction.h"

EcInteraction::EcInteraction(QObject *parent): QObject(parent)
{
    m_qpFriendList.reset(new FriendList(this));
    m_qpChat.reset(new Chat(this));
    m_qpGroupList.reset(new GroupModel(m_selfAccount));
}

void EcInteraction::sendMessage(QString jsonData)
{
    emit sig_sendMessage(jsonData);
}

FriendList *EcInteraction::getFriendList() const
{
    return m_qpFriendList.data();
}

GroupModel *EcInteraction::chatGroupList() const
{
    return m_qpGroupList.data();
}

Chat *EcInteraction::getChat() const
{
    return m_qpChat.data();
}

QString EcInteraction::selfAccount() const
{
    return m_selfAccount;
}

void EcInteraction::setSelfAccount(QString account)
{
    m_selfAccount = account;
    emit sig_selfAccountChanged(m_selfAccount);
    m_qpGroupList->setSelfAccount(m_selfAccount);
}

void EcInteraction::closeClientThread()
{
    emit sig_signOut(m_selfAccount);
}

QString EcInteraction::getRemarksName(QString friendAccount)
{
    return m_qpFriendList->getRemarksName(friendAccount);
}

void EcInteraction::setGroupSelected(QString GroupAccount)
{
    m_qpGroupList->setbSelected(GroupAccount);
}


