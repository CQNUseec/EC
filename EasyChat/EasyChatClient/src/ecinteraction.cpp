#include "ecinteraction.h"

EcInteraction::EcInteraction(QObject *parent): QObject(parent)
{
    m_qpFriendList.reset(new FriendList(this));
    m_qpChat.reset(new Chat(this));
}

void EcInteraction::sendMessage(QString jsonData)
{
    emit sig_sendMessage(jsonData);
}

FriendList *EcInteraction::getFriendList() const
{
    return m_qpFriendList.data();
}

Chat *EcInteraction::getChat() const
{
    return m_qpChat.data();
}

QString EcInteraction::getSystemFont() const
{
    return EC_SYSTEM_FONT;
}

QString EcInteraction::selfAccount() const
{
    return m_selfAccount;
}

void EcInteraction::setSelfAccount(QString account)
{
    m_selfAccount = account;
    emit sig_selfAccountChanged(m_selfAccount);
}

void EcInteraction::closeClientThread()
{
    emit sig_closeClientThread();
}


