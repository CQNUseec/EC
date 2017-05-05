#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <string>
#include <QtSql>
#include <iostream>
extern int number;
using namespace std;
//群信息相关
class group
{
public:
    group();

    //创建一个群组(groupAccount,GroupName,GroupOwner)
    string  addGroup(string groupName,
                        string groupOwner);

    //删除一个群组(只有组的创建者可以删除一个组)
    bool deleteGroup(string groupAccount);

    //获取一个群的所有者
    string getGroupOwner(string groupAccount);

    //获取一个组的群组号，组名,群主，群备注名”
    vector<string> getGroupInformation(string account);

    bool IsExsitInDB(string groupAccount);

};

#endif // GROUP_H
