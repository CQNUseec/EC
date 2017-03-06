#ifndef ECCLIENT_H
#define ECCLIENT_H
#include <QThread>

class EcClient: public QThread
{
public:
    EcClient(QString serverIp, QString serverPort);
//    void run();
private:
    QString          m_serverIp;
    QString          m_serverPort;
};

#endif // ECCLIENT_H
