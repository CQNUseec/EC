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
    if(purpose == 4 || purpose == 6 || purpose == 9)
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
//    auto thisMessageListModel = m_ecInteraction->getChat()->getOneMessageListModel(receiver);
//    if(nullptr != thisMessageListModel) //聊天窗口已创建，model存在
//    {
//        thisMessageListModel->loadDataToModel(sender, receiver, message, sendTime);
//        m_ecInteraction->getChat()->chatListModel()->setBUnreadMessage(sender, true);
//    }
//    else  //显示到主界面未读消息列表
//    {
//        QString senderName = m_ecInteraction->getFriendList()->getRemarksName(sender);
//        m_ecInteraction->getChat()->loadDataToChat(senderName, sender, receiver);
//        auto mainMessageMode = m_ecInteraction->mainMessageModel();
//        mainMessageMode->loadDataToModel(EC_NETWORK_SEND_MESSAGE, sender, receiver, message);
//    }
}
