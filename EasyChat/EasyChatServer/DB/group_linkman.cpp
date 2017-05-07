#include "group_linkman.h"
#include "DOMAIN/ecglobal.h"
#include "jsoncpp/json.h"

group_linkman::group_linkman()
{

}

QString group_linkman::addLinkmanToGroup(QString groupAccount, QString linkmanAccount, QString remarkname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO group_linkman(groupaccount, linkmanaccount,remarkname)"
                  "VALUES (:groupaccount,:linkmanaccount,:remarkname)");
    query.bindValue(":groupaccount", groupAccount);
    query.bindValue(":linkmanaccount", linkmanAccount);
    query.bindValue(":remarkname", remarkname);
    query.exec();
    return "add_linkman_to_group_success";
}

QString group_linkman::deleteLinkmanFromGroup(QString groupAccount)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM group_linkman "
                          "WHERE groupaccount='%1'").arg(groupAccount);
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

vector<string> group_linkman::getAccountAllGroup(QString linkmanAccount)
{
    vector<string> ret;
    Json::FastWriter fastWriter;

    QString infoInDB=QString("SELECT groupaccount,groupname,groupowner,remarkname FROM _group,group_linkman "
                             "WHERE group_linkman.linkmanaccount='%1' AND _group.account = group_linkman.groupaccount").arg(linkmanAccount);
    QSqlQuery query;
    query.exec();

    while(query.next())
    {
        Json::Value result_temp;
        string groupAccount = query.value(0).toString().toStdString();
        string groupName = query.value(1).toString().toStdString();
        string groupOwner = query.value(2).toString().toStdString();
        string remarkname = query.value(3).toString().toStdString();

        result_temp["purpose"] = EC_NETWORK_GROUP_LIST;
        result_temp["groupAccount"] = groupAccount;
        result_temp["groupName"] = groupName;
        result_temp["groupOwner"]=groupOwner;
        result_temp["remarksName"] = remarkname;

        std::string jsonStr = fastWriter.write(result_temp);
        ret.push_back(jsonStr);
    }
    return ret;
}
