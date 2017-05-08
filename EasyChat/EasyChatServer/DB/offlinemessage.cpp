#include "offlinemessage.h"
#include "jsoncpp/json.h"
#include "DOMAIN/ecglobal.h"

OfflineMessage::OfflineMessage()
{

}

bool OfflineMessage::addOfflineMessage(QString account, QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO offlinemessage(account, message)"
                  "VALUES(:account, :message)");
    query.bindValue(":account", account);
    query.bindValue(":message", message);
    if (query.exec())
        return true;
    else
        return false;
}

vector<string> OfflineMessage::getOfflineMessage(QString account)
{
    vector<string>  offline_message;

    QString find = QString("SELECT * FROM offlinemessage WHERE account='%1'").arg(account);
    QSqlQuery query;
    query.exec(find);
    while (query.next())
    {
        string message = query.value(1).toString().toStdString();
        offline_message.push_back(message);
    }
    return offline_message;
}

bool OfflineMessage::deleteOfflineMessage(QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM offlinemessage "
                             "WHERE account='%1'").arg(account);
    if(query.exec(del))
        return true;
    else
        return false;
}

bool OfflineMessage::IsExistOfflineMessage(QString account)
{
    QString find = QString("SELECT * FROM offlinemessage WHERE account='%1'").arg(account);
    QSqlQuery query;
    query.exec(find);

    if(query.next())
       return true;
    else
       return false;
}
