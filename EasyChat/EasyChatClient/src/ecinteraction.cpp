#include "ecinteraction.h"

void EcInteraction::logIn(QString account, QString password)
{
    emit sig_loginResult(true);   //测试用
}

EcInteraction::EcInteraction(QObject *parent): QObject(parent)
{
    m_qpFriendList.reset(new FriendList(this));
    m_qpChat.reset(new Chat(this));
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
    return SYSTEM_FONT;
}


