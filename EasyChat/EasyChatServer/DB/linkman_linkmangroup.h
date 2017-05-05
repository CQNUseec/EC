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
    QString addLinkmanToLinkmanGroup(QString m_account, QString m_linkmanAccount, QString m_linkmanGroupname, QString m_remarkName);
    //删除好友
    bool deleteLinkmanFromLinkmanGroup(QString account);

    //获取好友列表()
    vector<string> getAllLinkmanInformation(string account);

    //改变联系人所属组
    bool changeLinkmanGroup(QString account,QString linkmanAccount,QString linkmanGroupname);
};

#endif // LINKMAN_LINKMANGROUP_H
