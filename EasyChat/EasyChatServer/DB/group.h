#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <QtSql>
#include <iostream>

//群信息相关
class group
{
public:
    group();

    //创建一个群组(account(该群是谁创建的),groupAccount,GroupName,GroupOwner,remarkname)
    QString createGroup(QString groupAccount,QString groupName,
                        QString groupOwner);

    //删除一个群组(只有组的创建者可以删除一个组)
    QString deleteGroup(QString groupAccount,QString groupOwner);
};

#endif // GROUP_H
