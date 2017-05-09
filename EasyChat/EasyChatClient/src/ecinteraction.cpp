#include "ecinteraction.h"
#include "ecglobal.h"
EcInteraction::EcInteraction(QObject *parent): QObject(parent)
{
    m_qpFriendList.reset(new FriendList(this));
    m_qpChat.reset(new Chat(this));
    m_qpGroupList.reset(new GroupModel(m_selfAccount));
    m_mainMessageModel.reset(new MainMessageModel());
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

MainMessageModel *EcInteraction::mainMessageModel() const
{
    return m_mainMessageModel.data();
}

Chat *EcInteraction::getChat() const
{
    return m_qpChat.data();
}

QString EcInteraction::getAccountName(QString account)
{
    if(isGroupAccount(account))
        m_qpGroupList->getMemberName(account);
    else
    return m_qpFriendList->getRemarksName(account);
}

void EcInteraction::removeMainMessageModelData(int idNum)
{
    m_mainMessageModel->removeData(idNum);
}

bool EcInteraction::isGroupAccount(QString account)
{
    return m_qpGroupList->isGroupAccount(account);
}

void EcInteraction::slot_loadDataToChat(QStringList stringList)
{
    QString sender= stringList[0];
    QString receiver = stringList[1];
    QString message = stringList[2];
    QString sendTime = stringList[3];
    if(getChat()->isChatToSender(sender))  //聊天窗口已存在 直接显示
    {
        getChat()->getOneMessageListModel(sender)->loadDataToModel(sender, receiver, message, sendTime);
        emit getChat()->sig_viewChanged();
    }
    else    //缓存收到的消息
    {
        getChat()->loadDataToTemp(sender, receiver, message, sendTime);
        m_mainMessageModel->loadDataToModel(EC_NETWORK_SEND_MESSAGE, sender, receiver, message);
    }
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

void EcInteraction::closeClientThread(int i)
{
    if(i == 0)
        emit sig_signOut("0");
    else
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


