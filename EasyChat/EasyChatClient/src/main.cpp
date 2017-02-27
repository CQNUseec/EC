#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ecinteraction.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    EcInteraction  easyCaht(&app);
    easyCaht.getFriendList()->loadDataToModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("EcInteraction", &easyCaht);

    // 以下注册到qml界面的全局变量都可以封装为一个
    engine.rootContext()->setContextProperty("myFriend", easyCaht.getFriendList());
    engine.rootContext()->setContextProperty("friendList", easyCaht.getFriendList()->getFriendItemModel());
    engine.rootContext()->setContextProperty("chat", easyCaht.getChat());
    engine.rootContext()->setContextProperty("chatFriendList", easyCaht.getChat()->getChatFriendItemModel());
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
