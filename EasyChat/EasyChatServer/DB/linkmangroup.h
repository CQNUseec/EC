#ifndef LINKMANGROUP_H
#define LINKMANGROUP_H

#include <QString>
#include <QtSql>
#include <iostream>

class LinkmanGroup
{
public:
    LinkmanGroup();

    //创建联系人分组
    QString createLinkmanGroup(QString account, QString linkmanGroupName);

    //删除联系人分组
    QString deleteLinkmanGroup(QString account,QString linkmanGroupname);

};

#endif // LINKMANGROUP_H
