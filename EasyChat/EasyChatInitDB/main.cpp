#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include "initdb.h"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
  //  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if(createConnection())
    {
        createTableAccount();//
        createTableAccountTerminal();
        createTableDynamic();
        createTableGroup();
        createTableGroupLinkman();
        createTableLinkmanGroup();
        createTableLinkman_LinkmanGroup();
        createTableOfflineMessage();

        cout <<"create table success"<<endl;
    }
    else
    {
        cout<<"create db fail"<< endl;
    }

    return app.exec();
}
