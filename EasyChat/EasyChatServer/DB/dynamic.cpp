#include "dynamic.h"

dynamic::dynamic()
{

}

bool dynamic::addDynamic(QString dynamicId,QString account, QString content, QString time)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dynamic(dynamicId,account, content,time)"
                  "VALUES (:dynamicId,:account,:content,:time)");
    query.bindValue(":dynamicId",dynamicId);
    query.bindValue(":account", account);
    query.bindValue(":content",content);
    query.bindValue(":time", time);

    if(query.exec())
        return true;
    else
        return false;

}

bool dynamic::deleteDynamic(QString dynamicId, QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM dynamic "
                          "WHERE dynamicId='%1'AND account = %2").arg(dynamicId).arg(account);
    if(query.exec(del))
        return true;
    else
        return false;
}
