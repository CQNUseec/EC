#include "linkmangroup.h"

linkmanGroup::linkmanGroup()
{

}

QString linkmanGroup::createLinkmanGroup(QString account, QString linkmanGroupName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO linkmangroup(account,linkmanGroupname)"
                  "VALUES (:account,:linkmanGroupName)");
    query.bindValue(":account", account);
    query.bindValue(":linkmanGroupName", linkmanGroupName);
    query.exec();
    return "create_linkmanGroup_success";
}

QString linkmanGroup::deleteLinkmanGroup(QString account, QString linkmanGroupname)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM linkmangroup "
                          "WHERE account='%1' and linkmanGroup='%1'").arg(account,linkmanGroupname);
    query.exec(del);

    return "delete_linkmangroup_success";
}
