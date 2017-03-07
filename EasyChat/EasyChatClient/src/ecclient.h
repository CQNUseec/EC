#ifndef ECCLIENT_H
#define ECCLIENT_H
#include <QThread>

class EcInteraction;
class EcClient: public QThread
{
    Q_OBJECT
//signals:
//    void sig_receivedMessage(QString jsonData);
public slots:
    void slot_sendMessage(QString jsonData);
public:
    explicit EcClient();
    void run();
private:
    //EcInteraction*       m_ecInteraction;          //待定的成员变量
    QString              m_serverIp;
    QString              m_serverPort;
};

#endif // ECCLIENT_H
