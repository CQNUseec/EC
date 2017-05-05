#include "ecclientthread.h"
#include "ecclient.h"
#include "ecinteraction.h"

EcClientThread::EcClientThread(EcInteraction *ec): m_ecInteraction(ec)
{

}

void EcClientThread::run()
{
    try
    {
        qDebug() << "The client Thread running";
        EcClient client(m_ecInteraction);
        connect(&client, &EcClient::sig_closeClientThread, this, &EcClientThread::slot_closeClientThread);
        exec();
    }
    catch(std::exception  &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void EcClientThread::slot_closeClientThread()
{
    this->exit();
    qDebug() << "The client Thread exit";
}
