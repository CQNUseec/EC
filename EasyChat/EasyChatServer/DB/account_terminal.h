#ifndef ACCOUNT_TERMINAL_H
#define ACCOUNT_TERMINAL_H

#include <QString>
#include <QtSql>
#include <iostream>

class account_terminal
{
public:
    account_terminal();

    //上线
    QString addflag(QString account,QString flag);
    //下线
    QString deleteflag(QString account);
    //获取标志(用于发消息时用)
    QString getflag(QString account);

};

#endif // ACCOUNT_TERMINAL_H
