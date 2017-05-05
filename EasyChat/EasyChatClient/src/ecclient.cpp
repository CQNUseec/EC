#include "ecclient.h"
#include "ecinteraction.h"
#include <string>
#include <QJsonDocument>
#include <QThread>
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
    if(purpose == 4 || purpose == 6 || purpose == 9)
        m_qpNetWork->sendMessageOnly(jsonData.toStdString());
    else
        m_qpNetWork->sendMessageAndReceiver(jsonData.toStdString());
}

void EcClient::slot_messageFromServer(std::string data)
{
    analyzeMessageFromServer(data);
}

void EcClient::slot_signOut(QString account)
{
    if(account != "0")
    {

    }
    emit sig_closeClientThread();
}

void EcClient::analyzeMessageFromServer(std::string data)
{
    //    QString jsonData = QString::fromStdString(encryptionTheString(data, 'w'));
    QVariantMap result =  parsingJsonData(QString::fromStdString(data));
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
    emit m_ecInteraction->sig_loginResult(result["result"].toInt());
}

void EcClient::registerRes(QVariantMap &result)
{
    emit m_ecInteraction->sig_registerAccountResult(result["account"].toString());
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
    auto thisMessageListModel = m_ecInteraction->getChat()->getOneMessageListModel(receiver);
   if(nullptr != thisMessageListModel)
   {
       thisMessageListModel->loadDataToModel(sender, receiver, message, sendTime);
       m_ecInteraction->getChat()->chatListModel()->setBUnreadMessage(sender, true);
   }
   else
   {
       m_ecInteraction->getChat()->loadDataToChat("sender", sender, receiver);
   }
}
