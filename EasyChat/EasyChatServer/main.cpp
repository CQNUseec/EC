#include <QCoreApplication>
#include <memory>

#include "DOMAIN/server.h"
#include "DOMAIN/chatcontrol.h"

int number=111111;

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("easychat");
    db.setUserName("easychat");
    db.setPassword("easychat");
    if(!db.open())
    {
         return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(createConnection())
        cout <<"connetction success"<<endl;
    else
        cout <<"connetion"<<endl;

//    linkman_linkmanGroup ll;
//    ll.addLinkmanToLinkmanGroup("111112","111111","friend","test1");
//    ll.addLinkmanToLinkmanGroup("111112","111113","friend","test1");

    try
    {
        cout<<"Server start..."<<endl;
        Server srv;

        std::shared_ptr<ChatControl> ptr = std::make_shared<ChatControl>();
        srv.setPtr(ptr);

        srv.run();

    }
    catch(std::exception & e)
    {
        cout<<e.what()<<endl;
    }

    return a.exec();


}
