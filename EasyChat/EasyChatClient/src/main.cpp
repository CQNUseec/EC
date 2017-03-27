#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ecinteraction.h"
#include "ecclientthread.h"
#include <QString>
#include "singleApplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    SingleApplication app(argc, argv);
    if(app.isRunning())
        return 0;
    EcInteraction  easyCaht(&app);
    easyCaht.getFriendList()->loadDataToModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("EcInteraction", &easyCaht);
    engine.rootContext()->setContextProperty("friendListModel", easyCaht.getFriendList()->getFriendItemModel());
    engine.rootContext()->setContextProperty("SystemFont", EC_SYSTEM_FONT);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    EcClientThread client(&easyCaht);
    client.start();
    return app.exec();
}
