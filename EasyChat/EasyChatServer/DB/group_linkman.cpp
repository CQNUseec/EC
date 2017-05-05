#include "group_linkman.h"

group_linkman::group_linkman()
{

}

QString group_linkman::addLinkmanToGroup(QString groupAccount, QString linkmanAccount, QString remarkname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO group_linkman(groupAccount, linkmanAccount,remarkname)"
                  "VALUES (:groupAccount,:linkmanAccount,:remarkname)");
    query.bindValue(":groupAccount", groupAccount);
    query.bindValue(":linkmanAccount", linkmanAccount);
    query.bindValue(":remarkname", remarkname);
    query.exec();
    return "add_linkman_to_group_success";
}

QString group_linkman::deleteLinkmanFromGroup(QString groupAccount)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM group_linkman "
                          "WHERE groupAccount='%1'").arg(groupAccount);
    query.exec(del);
    return "delete_linkman_form_group_success";
}

QString group_linkman::remarkGroupname(QString groupAccount, QString remarkname)
{
    QString update = QString("UPDATE group_linkman set remarkname='%1'"
                             "WHERE groupAccount= '%2'").arg(remarkname).arg(groupAccount);
    QSqlQuery query;
    query.exec(update);
    return "remark_Groupname_success";
}

vector<QString> group_linkman::getAllLinkmanOfGroup(QString groupAccount)
{


}
