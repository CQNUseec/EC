#include "ecinteraction.h"
#include <QThread>
#include <QJsonDocument>

EcInteraction::EcInteraction(QObject *parent): QObject(parent)
{
    m_qpFriendList.reset(new FriendList(this));
    m_qpChat.reset(new Chat(this));
}

void EcInteraction::sendMessage(QString jsonData)
{
    emit sig_sendMessage(jsonData);
}

void EcInteraction::logIn(QString account, QString password)
{
    if(account == "111111")
        emit sig_loginResult(EC_LOGIN_RESULT_INVALID_ACCOUNT);
    else if(password == "easychat")
        emit sig_loginResult(EC_LOGIN_RESULT_SUCCESSFUL);
    else if(account == "123456")
        emit sig_loginResult(EC_LOGIN_RESULT_SUCCESSFUL);
    else
        emit sig_loginResult(EC_LOGIN_RESULT_WRONG_PASSWORD);
}

void EcInteraction::registerAccount(QString jsonData)
{
    qDebug() << jsonData;
    parsingJsonData(jsonData);
    emit sig_registerAccountResult(1, "123456");
}

FriendList *EcInteraction::getFriendList() const
{
    return m_qpFriendList.data();
}

Chat *EcInteraction::getChat() const
{
    return m_qpChat.data();
}

void EcInteraction::parsingJsonData(QString jsonData)
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (jsonDocument.isObject())
        {
            QVariantMap result = jsonDocument.toVariant().toMap();
            qDebug() << result["purpose"].toString();
        }
    }
}

QString EcInteraction::getSystemFont() const
{
    return EC_SYSTEM_FONT;
}


