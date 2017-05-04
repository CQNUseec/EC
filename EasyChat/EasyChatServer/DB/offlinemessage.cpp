#include "offlinemessage.h"

offlineMessage::offlineMessage()
{

}

QString offlineMessage::addOfflineMessage(QString account, QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO OfflineMessage(account, message)"
                  "VALUES(:account, :message)");
    query.bindValue(":account", account);
    query.bindValue(":message", message);
    query.exec();
    return "add_offlineMessage_success";
}

vector<QString> offlineMessage::getOfflineMessage(QString account)
{
    vector<QString>  offline_message;
    QString find = QString("SELECT * FROM OfflineMessage WHERE account='%1'").arg(account);
    QSqlQuery query;
    query.exec(find);
    while (query.next())
    {
        QString message = query.value(0).toString();
        offline_message.push_back(message);
    }
    return offline_message;
}

QString offlineMessage::deleteOfflineMessage(QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM OfflineMessage "
                             "WHERE account='%1'").arg(account);
    query.exec(del);
    return "delete_offline_message_success";
}
