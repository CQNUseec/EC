#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <vector>
using namespace std;


//帐号相关
class account
{
public:
    account();
    //注册帐号
    QString registerAcount(QString account,QString password,QString nickname,
                           QString sex,QString age);
    //分配帐号(用于注册时)
   QString assignAccount();

   //登录
   QString login(QString account,QString password);

   //查找用户信息,用于加好友时(输入一个帐号查找这个帐号的相关信息)
   vector<QString> find(QString account);
};

#endif // ACCOUNT_H
