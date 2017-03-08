#include "ecclientthread.h"
#include "ecclient.h"
#include "ecinteraction.h"

EcClientThread::EcClientThread(EcInteraction *ec): m_ecInteraction(ec)
{

}

void EcClientThread::run()
{
    qDebug() << "The client Thread running";
    EcClient client(m_ecInteraction);
    exec();
}
