#ifndef OFFLINEMESSAGE_H
#define OFFLINEMESSAGE_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
using namespace std;

class OfflineMessage
{
public:
    OfflineMessage();
    //添加离线消息
    bool addOfflineMessage(QString account,QString message);
    //获取某人的离线消息
    vector<string> getOfflineMessage(QString account);
    //删除某人的离线消息
    bool deleteOfflineMessage(QString account);

    //判断是否有离线消息
    bool IsExistOfflineMessage(QString account);
};

#endif // OFFLINEMESSAGE_H
