#include "ecclient.h"
#include "ecinteraction.h"
#include <string>
#include <QJsonDocument>
#include <QThread>
#include <boost/thread.hpp>
using std::string;

EcClient::EcClient(EcInteraction* ecInteraction) : m_ecInteraction(ecInteraction)
{
    //192.168.43.17
    m_qpNetWork.reset(new NetWork("192.168.43.17", 6688));
    //   m_qpNetWork->run();
    connect(m_qpNetWork.data(), &NetWork::sig_messageFromServer, this, &EcClient::slot_messageFromServer);
    connect(ecInteraction, &EcInteraction::sig_sendMessage, this, &EcClient::slot_sendMessage, Qt::QueuedConnection);
    connect(ecInteraction, &EcInteraction::sig_signOut, this, &EcClient::slot_signOut, Qt::BlockingQueuedConnection);
    connect(this, &EcClient::sig_loadDataToFriendList, m_ecInteraction->getFriendList(), &FriendList::slot_loadDataToFriendList);
    connect(this, &EcClient::sig_loadDataToChat, ecInteraction, &EcInteraction::slot_loadDataToChat);
}

string encryptionTheString(string data, char key)   //对字符串进行异或运算
{
    string res;
    for(auto &var : data)
    {
        res += var ^ key;
    }
    return res;
}
void EcClient::slot_sendMessage(QString jsonData)
{
    qDebug() << "EcClient Thead print: " << jsonData;
    QVariantMap result =  parsingJsonData(jsonData);
    int purpose = result["purpose"].toInt();
    if(purpose == EC_NETWORK_SEND_MESSAGE || purpose == EC_NETWORK_ADD_FRIEND
            || purpose == EC_NETWORK_LOGOUT)
        m_qpNetWork->sendMessageOnly(jsonData.toStdString());
    else
        m_qpNetWork->sendMessageAndReceiver(jsonData.toStdString());
}

void EcClient::slot_messageFromServer(QString data)
{
    std::cout << data.toStdString() << std::endl;
    analyzeMessageFromServer(data);
}

void EcClient::slot_signOut(QString account)
{
    if(account != "0")
    {
        QString jsonData = QString("{\"purpose\":9,\"account\":\"%1\"}").arg(account);
        m_qpNetWork->sendMessageOnly(jsonData.toStdString());
    }
    emit sig_closeClientThread();
}

void EcClient::analyzeMessageFromServer(QString data)
{
    //    QString jsonData = QString::fromStdString(encryptionTheString(data, 'w'));
    QVariantMap result =  parsingJsonData(data);
    if(result.isEmpty())
        return;
    qDebug() << "AnalyzeMessageFromServer: " << result;
    //    QThread::sleep(1);
    switch (result["purpose"].toInt())
    {
    case EC_NETWORK_LOGIN:
        loginRes(result);
        break;
    case EC_NETWORK_REGISTER:
        registerRes(result);
        break;
    case EC_NETWORK_FRIEND_LIST:
        loadDataToFriendList(result);
        break;
    case EC_NETWORK_SEND_MESSAGE:
        loadChatMessageData(result);
        break;
    case EC_NETWORK_GROUP_LIST:
        loadDataToGruoupList(result);
        break;
    case EC_NETWORK_FIND_ACCOUNT:
        findUserRes(result);
        break;
    case EC_NETWORK_ADD_FRIEND:
        addFriendRes(result);
        break;
    default:
        break;
    }
}

QVariantMap EcClient::parsingJsonData(QString jsonData)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (jsonDocument.isObject())
        {
            return jsonDocument.toVariant().toMap();
        }
    }
    return QVariantMap();
}

void EcClient::loginRes(QVariantMap &result)
{
    int tmp = result["result"].toInt();
    emit m_ecInteraction->sig_loginResult(tmp);
    if(tmp == EC_LOGIN_RESULT_SUCCESSFUL)  //登录成功，启动消息监听
    {
        boost::thread udpThread([&]{m_qpNetWork->accept();});
        udpThread.detach();;
    }
}

void EcClient::registerRes(QVariantMap &result)
{
    emit m_ecInteraction->sig_registerAccountResult(result["account"].toString());
}

void EcClient::findUserRes(QVariantMap &result)
{
    QString res = result["result"].toString();
    if(res == "OK")
    {
        QString nickName = result["nickName"].toString();
        QString age = result["age"].toString();
        QString sex = result["sex"].toString();
        emit m_ecInteraction->sig_findAccountResult(res, nickName, age, sex);
    }
    else
        emit m_ecInteraction->sig_findAccountResult(res);

}

void EcClient::addFriendRes(QVariantMap &result)
{
    QString initiated = result["initiated"].toString();
    QString aims = result["aims"].toString();
    int type = result["purpose"].toInt();
    m_ecInteraction->mainMessageModel()->loadDataToModel(type, initiated, aims, "添加好友请求");
}

void EcClient::loadDataToFriendList(QVariantMap &result)
{
    QStringList stringList;
    stringList.append(result["groupName"].toString());
    stringList.append(result["account"].toString());
    stringList.append(result["nickName"].toString());
    stringList.append(result["remarksName"].toString());
    emit sig_loadDataToFriendList(stringList);
    //    m_ecInteraction->getFriendList()->loadDataToModel(result["groupName"].toString(),
    //            result["account"].toString(), result["nickName"].toString(),
    //            result["remarksName"].toString());
}

void EcClient::loadChatMessageData(QVariantMap &result)
{
    QString receiver = result["receiver"].toString();
    QString sender = result["sender"].toString();
    QString message = result["message"].toString();
    QString sendTime = result["sendTime"].toString();
    QStringList strList;
    strList.append(sender);
    strList.append(receiver);
    strList.append(message);
    strList.append(sendTime);
    emit sig_loadDataToChat(strList);
}

void EcClient::loadDataToGruoupList(QVariantMap &result)
{
    QString groupAccount = result["groupAccount"].toString();
    QString groupName = result["groupName"].toString();
    QString groupOwner = result["groupOwner"].toString();
    QString remarksName = result["remarksName"].toString();
    QStringList temp;
    m_ecInteraction->chatGroupList()->loadDataToModel(groupAccount, groupName, groupOwner);
}
