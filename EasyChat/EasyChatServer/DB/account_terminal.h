#ifndef ACCOUNT_TERMINAL_H
#define ACCOUNT_TERMINAL_H

#include <QString>
#include <QtSql>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class account_terminal
{
public:
    account_terminal();

    //上线
    bool addflag(QString account,QString flag);
    //下线
    bool deleteflag(QString account);
    //获取标志(用于发消息时用)
    string getflag(QString account);

    bool isOnline(QString account);

};

#endif // ACCOUNT_TERMINAL_H
