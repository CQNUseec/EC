#ifndef GROUP_LINKMAN_H
#define GROUP_LINKMAN_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
using namespace std;

//群聊的关联（remark表示一个人对这个群的备注）
class group_linkman
{
public:
    group_linkman();

    //群聊的时候加人到群组里面
    QString addLinkmanToGroup(QString groupAccount,QString linkmanAccount,QString remarkname);
    //退群,群主踢人
    QString deleteLinkmanFromGroup(QString groupAccount);
    //改群备注
    QString remarkGroupname(QString groupAccount,QString remarkname);
    //获取一个群的所有人（关联）
    vector<QString> getAllLinkmanOfGroup(QString groupAccount);

    //获取一个人所在的所有群
    vector<string> getAccountAllGroup(QString linkmanAccount);

};

#endif // GROUP_LINKMAN_H
