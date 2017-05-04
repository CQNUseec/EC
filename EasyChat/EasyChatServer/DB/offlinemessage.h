#ifndef OFFLINEMESSAGE_H
#define OFFLINEMESSAGE_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
using namespace std;

class offlineMessage
{
public:
    offlineMessage();
    //添加离线消息
    QString addOfflineMessage(QString account,QString message);
    //获取某人的离线消息
    vector<QString> getOfflineMessage(QString account);
    //删除某人的离线消息
    QString deleteOfflineMessage(QString account);
};

#endif // OFFLINEMESSAGE_H
