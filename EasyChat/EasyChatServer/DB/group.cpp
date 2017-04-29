#include "group.h"

group::group()
{

}

QString group::createGroup(QString groupAccount, QString groupName, QString groupOwner)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Group(groupAccount, groupName,groupOwner)"
                  "VALUES (:groupAccount,groupName,groupOwner)");
    query.bindValue(":groupAccount", groupAccount);
    query.bindValue(":groupName", groupName);
    query.bindValue(":groupOwner", groupOwner);
    query.exec();
    return "create_group_success";
}

//只有群主可以删除组
QString group::deleteGroup(QString groupAccount, QString groupOwner)
{
    QString infoInDB=QString("SELECT groupOwner FROM Group "
                     "WHERE groupAccount = '%1'").arg(groupAccount);
    QSqlQuery query;

    query.exec(infoInDB);

    if(query.next())
    {
        QString gowner=query.value(0).toString();
        if(groupOwner == gowner)
        {
            QString del = QString("DELETE FROM Group "
                                  "WHERE groupAccount='%1'").arg(groupAccount);
            query.exec(del);

            return "delete_group_success";
        }
        else
            return "permission_denied";
    }
}
