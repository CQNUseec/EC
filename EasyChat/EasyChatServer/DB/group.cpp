#include "group.h"
#include "group_linkman.h"
#include <time.h>

Group::Group()
{

}

string Group::addGroup(string groupName, string groupOwner)
{
    QString groupaccount;
    do{
        srand(time(NULL));
        int act=rand()%100000+200000;
        groupaccount = QString::number(act);
    }while(IsExsitInDB(groupaccount.toStdString()));

    QSqlQuery query;
    query.prepare("INSERT INTO _group(groupaccount, groupname,groupowner)"
                  "VALUES (:groupaccount,:groupname,:groupowner)");
    query.bindValue(":groupaccount", groupaccount);
    query.bindValue(":groupname",QString::fromStdString(groupName));
    query.bindValue(":groupowner", QString::fromStdString(groupOwner));

    query.exec();

    //创建一个组成功后，创建自身与这个组的关联
    group_linkman gl;
    gl.addLinkmanToGroup(groupaccount,QString::fromStdString(groupOwner),QString::fromStdString(groupName));

    return groupaccount.toStdString();
}

bool Group::deleteGroup(string groupAccount)
{
    QSqlQuery query;
    QString gpa = QString::fromStdString(groupAccount);
    QString del = QString("DELETE FROM _group "
                          "WHERE groupaccount='%1'").arg(gpa);
    if(query.exec(del))
        return true;
    else
        return false;
}

string Group::getGroupOwner(string groupAccount)
{
    QString gpa = QString::fromStdString(groupAccount);
    QString infoInDB=QString("SELECT groupowner FROM _group "
                     "WHERE groupaccount = '%1'").arg(gpa);
    QSqlQuery query;

    query.exec(infoInDB);

    if(query.next())
    {
        QString gowner=query.value(0).toString();
        return gowner.toStdString();
    }
    return "";
}

vector<string> Group::getAllGroup(string groupOwner)
{
    vector<string> ret;
    QString ac = QString::fromStdString(groupOwner);
    QString infoInDB=QString("SELECT * FROM _group "
                     "WHERE account = '%1'").arg(ac);
    QSqlQuery query;
    query.exec(infoInDB);

    while(query.next())
    {

    }
    return ret;
}

bool Group::IsExsitInDB(string groupAccount)
{

    QString ac = QString::fromStdString(groupAccount);
    QString infoInDB=QString("SELECT * FROM _group "
                             "WHERE groupaccount = '%1'").arg(ac);
    QSqlQuery query;
    query.exec(infoInDB);

    if(query.next())
        return true;
    else
        return false;
}
