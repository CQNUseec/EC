#ifndef ECCLIENT_H
#define ECCLIENT_H
#include <QSharedPointer>
#include <QString>
#include <QVariant>
#include "network.h"
using std::string;

class EcInteraction;
class EcClient: public QObject             //客户端对象， 与服务器进行通信
{
    Q_OBJECT
signals:
    void sig_closeClientThread();
public slots:
    void slot_sendMessage(QString jsonData);
    void slot_messageFromServer(string data);
    void slot_signOut(QString account);
public:
    explicit EcClient(EcInteraction* ecInteraction);
    void analyzeMessageFromServer(std::string data);
private:
    QVariantMap parsingJsonData(QString jsonData);   //解析json格式字符
    void loginRes(QVariantMap &result);
    void registerRes(QVariantMap &result);
private:
    EcInteraction*                       m_ecInteraction;
    QString                              m_serverIp;
    QString                              m_serverPort;
    QSharedPointer<NetWork>              m_qpNetWork;
};

#endif // ECCLIENT_H
