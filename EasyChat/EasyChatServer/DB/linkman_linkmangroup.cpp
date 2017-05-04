#include "linkman_linkmangroup.h"

linkman_linkmanGroup::linkman_linkmanGroup()
{

}

QString linkman_linkmanGroup::addLinkmanToLinkmanGroup(QString account, QString linkmanAccount, QString linkmanGroupname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Linkman_LinkmanGroup(account, linkmanAccount,linkmanGroupname)"
                  "VALUES (:account,linkmanAccount,linkmanGroupname)");
    query.bindValue(":account", account);
    query.bindValue(":linkmanAccount", linkmanAccount);
    query.bindValue(":linkmanGroupname", linkmanGroupname);
    query.exec();
    return "add_linkman_to_linkmanGroup_success";
}

QString linkman_linkmanGroup::deleteLinkmanFromLinkmanGroup(QString account, QString linkmanAccount,QString linkmanGroupname)
{

}

QString linkman_linkmanGroup::changeLinkmanGroup(QString account, QString linkmanAccount, QString linkmanGroupname)
{

}
