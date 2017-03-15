#ifndef ECCLIENTTHREAD_H
#define ECCLIENTTHREAD_H
#include <QThread>

class EcClient;
class EcInteraction;
class EcClientThread : public QThread                 //客户端线程对象，在这个线程里面启动客户端（run()函数里面）
{
public:
    EcClientThread(EcInteraction *ec);
    void run();
public slots:
    void slot_closeClientThread();
private:
    EcInteraction*                   m_ecInteraction;
};

#endif // ECCLIENTTHREAD_H
