#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <string>
#include <QtSql>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
extern int number;


//帐号相关
class Account
{
public:
    Account();

    //注册帐号
    string addAcountInformation(string password,string nickname,
                           string sex,string age);
   //用于登录
   string getPassword(string account);

   //除了密码以外的其他属性
   vector<string> getAccountInformation(string account);

   //判断一个用户是否存在
   bool isAccountExist(string account);
};

#endif // ACCOUNT_H
