#include "ecclient.h"
#include "ecinteraction.h"
#include <string>
#include <QJsonDocument>
#include <QThread>
using std::string;

EcClient::EcClient(EcInteraction* ecInteraction) : m_ecInteraction(ecInteraction)
{
    m_qpNetWork.reset(new NetWork("192.168.43.17", 6688));
//   m_qpNetWork->run();
    connect(m_qpNetWork.data(), &NetWork::sig_messageFromServer, this, &EcClient::slot_messageFromServer);
    connect(ecInteraction, &EcInteraction::sig_sendMessage, this, &EcClient::slot_sendMessage, Qt::QueuedConnection);
    connect(ecInteraction, &EcInteraction::sig_signOut, this, &EcClient::slot_signOut, Qt::BlockingQueuedConnection);
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
//    string data = encryptionTheString(jsonData.toStdString(), 'w');
    m_qpNetWork->sendMessage(jsonData.toStdString());
//    qDebug() << "模拟发送给服务器的消息:" << QString::fromStdString(data) << data.length();
    //    analyzeMessageFromServer(data);
}

void EcClient::slot_messageFromServer(std::string data)
{
    analyzeMessageFromServer(data);
}

void EcClient::slot_signOut(QString account)
{
    if(account != "0")
        qDebug() << account << "sign out";
    emit sig_closeClientThread();
}

void EcClient::analyzeMessageFromServer(std::string data)
{
    QString jsonData = QString::fromStdString(encryptionTheString(data, 'w'));
    QVariantMap result =  parsingJsonData(jsonData);
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

    default:
        break;
    }
//    if(result["purpose"].toInt() == 1)  //测试用
//    {
//        if(result["password"].toString() == "easychat")
//            emit m_ecInteraction->sig_loginResult(EC_LOGIN_RESULT_SUCCESSFUL);
//        else if(result["account"].toString() == "111111")
//            emit m_ecInteraction->sig_loginResult(EC_LOGIN_RESULT_INVALID_ACCOUNT);
//        else if(result["account"].toString() == "123456")
//            emit m_ecInteraction->sig_loginResult(EC_LOGIN_RESULT_SUCCESSFUL);
//        else
//            emit m_ecInteraction->sig_loginResult(EC_LOGIN_RESULT_WRONG_PASSWORD);
//    }
//    else if(result["purpose"].toString() == "register")  //测试用
//        emit m_ecInteraction->sig_registerAccountResult("123456");
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
