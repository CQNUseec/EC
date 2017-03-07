#include "ecclient.h"
#include "ecinteraction.h"

EcClient::EcClient()
{

}

void EcClient::slot_sendMessage(QString jsonData)
{
    qDebug() << "EcClient THhead print: " << jsonData;
}



void EcClient::run()
{
    qDebug() <<"EcClient Running";
}
