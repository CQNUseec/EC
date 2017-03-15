#include "ecclientthread.h"
#include "ecclient.h"
#include "ecinteraction.h"

EcClientThread::EcClientThread(EcInteraction *ec): m_ecInteraction(ec)
{
    connect(ec, &EcInteraction::sig_closeClientThread, this, &EcClientThread::slot_closeClientThread);
}

void EcClientThread::run()
{
        qDebug() << "The client Thread running";
        EcClient client(m_ecInteraction);
        exec();
}

void EcClientThread::slot_closeClientThread()
{
    this->exit();
    qDebug() << "The client Thread exit";
}
