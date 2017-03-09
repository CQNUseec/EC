#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ecinteraction.h"
#include "ecclientthread.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    EcInteraction  easyCaht(&app);
    easyCaht.getFriendList()->loadDataToModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("EcInteraction", &easyCaht);

    engine.rootContext()->setContextProperty("myFriend", easyCaht.getFriendList());
    engine.rootContext()->setContextProperty("friendList", easyCaht.getFriendList()->getFriendItemModel());
    engine.rootContext()->setContextProperty("chat", easyCaht.getChat());
    engine.rootContext()->setContextProperty("chatFriendList", easyCaht.getChat()->getChatFriendItemModel());
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    EcClientThread client(&easyCaht);
    client.start();
    return app.exec();
}
