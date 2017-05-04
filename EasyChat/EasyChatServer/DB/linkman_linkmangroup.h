#ifndef LINKMAN_LINKMANGROUP_H
#define LINKMAN_LINKMANGROUP_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
using namespace std;

class linkman_linkmanGroup
{
public:
    linkman_linkmanGroup();

    //添加联系人到联系人组(加好友)
    QString addLinkmanToLinkmanGroup(QString account,QString linkmanAccount,QString linkmanGroupname);
    //删除
    QString deleteLinkmanFromLinkmanGroup(QString account,QString linkmanAccount,QString );

    //改变联系人所属组
    QString changeLinkmanGroup(QString account,QString linkmanAccount,QString linkmanGroupname);
};

#endif // LINKMAN_LINKMANGROUP_H
