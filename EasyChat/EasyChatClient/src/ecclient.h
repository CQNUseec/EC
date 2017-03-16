#ifndef ECCLIENT_H
#define ECCLIENT_H
#include <QString>
#include <QVariant>

class EcInteraction;
class EcClient: public QObject             //客户端对象， 与服务器进行通信
{
    Q_OBJECT
signals:
    void sig_closeClientThread();
public slots:
    void slot_sendMessage(QString jsonData);
    void slot_signOut(QString account);
public:
    explicit EcClient(EcInteraction* ecInteraction);
    void AnalyzeMessageFromServer(std::string data);
    QVariantMap parsingJsonData(QString jsonData);   //解析json格式字符
private:
    EcInteraction*       m_ecInteraction;
    QString              m_serverIp;
    QString              m_serverPort;
};

#endif // ECCLIENT_H
