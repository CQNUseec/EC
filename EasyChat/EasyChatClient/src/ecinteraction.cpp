#include "ecinteraction.h"

void EcInteraction::logIn(QString account, QString password)
{
    if(account == "111111")
        emit sig_loginResult(EC_LOGIN_RESULT_INVALID_ACCOUNT);
    else if(password == "easychat")
        emit sig_loginResult(EC_LOGIN_RESULT_SUCCESSFUL);
    else
        emit sig_loginResult(EC_LOGIN_RESULT_WRONG_PASSWORD);
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
    return EC_SYSTEM_FONT;
}


