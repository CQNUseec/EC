#include "linkman_linkmangroup.h"
#include "jsoncpp/json.h"
#include "DOMAIN/ecglobal.h"

linkman_linkmanGroup::linkman_linkmanGroup()
{

}

QString linkman_linkmanGroup::addLinkmanToLinkmanGroup(QString m_account, QString m_linkmanAccount, QString m_linkmanGroupname,QString m_remarkName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO linkman_linkmangroup(account, linkmanaccount,linkmangroupname,remarkname)"
                  "VALUES (:account,:linkmanaccount,:linkmangroupname,:remarkname)");
    query.bindValue(":account", m_account);
    query.bindValue(":linkmanaccount", m_linkmanAccount);
    query.bindValue(":linkmangroupname", m_linkmanGroupname);
    query.bindValue(":remarkname",m_remarkName);
    query.exec();
    return "add_linkman_to_linkmanGroup_success";
}

bool linkman_linkmanGroup::deleteLinkmanFromLinkmanGroup(QString account)
{
    QSqlQuery query;
    QString del = QString("DELETE FROM linkman_linkmangroup "
                          "WHERE groupaccount='%1'").arg(account);
    if(query.exec(del))
        return true;
    else
        return false;

}

vector<string> linkman_linkmanGroup::getAllLinkmanInformation(string account)
{
    vector<string> ret;
    Json::FastWriter fastWriter;

    QString ac = QString::fromStdString(account);
    QString infoInDB=QString("SELECT linkmangroupname,linkmanaccount,nickname,remarkname FROM account,linkman_linkmangroup "
                             "WHERE linkman_linkmangroup.account='%1' AND linkman_linkmangroup.linkmanaccount = account.account").arg(ac);
    QSqlQuery query;

    query.exec(infoInDB);

//联系人组,联系人帐号，备注
    while(query.next())
    {
        Json::Value result_temp;
        string groupname = query.value(0).toString().toStdString();
        string linkmanAccount = query.value(1).toString().toStdString();
        string nickname = query.value(2).toString().toStdString();
        string remarkname = query.value(3).toString().toStdString();

        result_temp["purpose"] = EC_NETWORK_FRIEND_LIST;
        result_temp["groupName"] = groupname;
        result_temp["account"] = linkmanAccount;
        result_temp["nickName"]=nickname;
        result_temp["remarksName"] = remarkname;

        std::string jsonStr = fastWriter.write(result_temp);

        cout << "数据库获取好友列表"<<endl;
        ret.push_back(jsonStr);
    }

    return ret;

}

string linkman_linkmanGroup::getALinkmanInfo(QString account, QString linkmanAccount)
{
    string ret;
    Json::FastWriter fastWriter;

    QString infoInDB=QString("SELECT linkmangroupname,linkmanaccount,nickname,remarkname FROM account,linkman_linkmangroup "
                             "WHERE linkman_linkmangroup.account='%1' AND linkman_linkmangroup.linkmanaccount='%2' AND linkman_linkmangroup.linkmanaccount = account.account").arg(account).arg(linkmanAccount);
    QSqlQuery query;

    query.exec(infoInDB);

    if(query.next())
    {
        Json::Value result_temp;
        string groupname = query.value(0).toString().toStdString();
        string linkmanAccount = query.value(1).toString().toStdString();
        string nickname = query.value(2).toString().toStdString();
        string remarkname = query.value(3).toString().toStdString();

        result_temp["purpose"] = EC_NETWORK_FRIEND_LIST;
        result_temp["groupName"] = groupname;
        result_temp["account"] = linkmanAccount;
        result_temp["nickName"]=nickname;
        result_temp["remarksName"] = remarkname;

        std::string jsonStr = fastWriter.write(result_temp);

        cout << "数据库获取好友列表"<<endl;

        ret = jsonStr;
    }
    return ret;
}

bool linkman_linkmanGroup::changeLinkmanGroup(QString account, QString linkmanAccount, QString linkmanGroupname)
{
    QString update = QString("UPDATE linkman_linkmangroup SET remarkname='%1'"
                             "WHERE account = %2 AND groupAccount= '%3'").arg(linkmanGroupname).arg(account).arg(linkmanAccount);
    QSqlQuery query;

    if(query.exec(update))
        return true;
    else
        return false;
}

bool linkman_linkmanGroup::isLinkExist(QString account, QString aim)
{
    QString infoInDB=QString("SELECT * FROM linkman_linkmangroup "
                             "WHERE account='%1' AND linkmanaccout='%2'").arg(account).arg(aim);
    QSqlQuery query;

    query.exec(infoInDB);

    if(query.next())
        return true;
    else
        return false;
}

//vector<string> linkman_linkmanGroup::listAccountAllGroup(QString account)
//{

//}
