#ifndef CHATCONTROL_H
#define CHATCONTROL_H
#include <jsoncpp/json.h>
#include <string>
#include <QString>
#include "DB/account.h"
#include "DB/offlinemessage.h"
#include "DB/group.h"
#include "DB/linkman_linkmangroup.h"
#include "DOMAIN/ecglobal.h"


using namespace std;







class chatControl
{
public:
    chatControl();


    //登录
    string login(string account,string password);
    //注册
    string registerAccount(string password,string nickname,string sex,string age);
    //查找
    string findAccountInfo(string account);

    //获取联系人列表
    vector<string> getLinkmanList(string account);

    //建群
    string createGroup(string groupName, string groupOwner);
    //获取离线消息
    string getOfflineMessage(string account);



public:
    static string encryptionTheString(string data, char key);
};

#endif // CHATCONTROL_H
