#include <QGuiApplication>
#include <QQmlApplicationEngine>
<<<<<<< HEAD
#include <iostream>
#include "initdb.h"

using namespace std;
=======
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
<<<<<<< HEAD
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
=======
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
>>>>>>> 008efbef92568ad556fbc6589e9ee854a844217a

    return app.exec();
}
