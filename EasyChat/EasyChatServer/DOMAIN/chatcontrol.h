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
#include "DB/account_terminal.h"
#include "DB/group_linkman.h"


using namespace std;


class ChatControl
{
public:
    ChatControl();


    //登录
    string login(string account,string password);

    //注册
    string registerAccount(string password,string nickname,string sex,string age);

    //查找
    string findAccountInfo(string account);

    //获取联系人列表
    vector<string> getLinkmanList(string account);

    string getALinkmanInfo(string account,string linkmanAccount);

    //建群
    string createGroup(string groupName, string groupOwner);

    //获取群列表
    vector<string> getGroupList(string account);

    //获取离线消息
    vector<string> getOfflineMessage(string account);

    //添加在线标志
    bool addOnlineFlag(string account,string flag);

    //删除在线标志
    bool deleteOnlineFlag(string account);

    //是否在线
    bool IsOnline(string account);

    //获取联系人通信标识
    string getAccountTerminalFlag(string account);

    //是否有离线消息
    bool IsExistOfflineMessage(string account);

    //添加离线消息
    bool addOfflineMessage(string account,string message);

    //删除离线消息
    bool deleteOfflineMessage(string account);

    //注销
    bool logout(string account);

    //同意添加好友
    int agreeAddFriend(string initiated,string aims);

    bool isGroup(string account);

    //获取一个组的所有成员帐号
    vector<string> getGroupAccounts(string account);

    //获取一个组所有成员的详细信息
    vector<string> getGroupInfo(string account);
public:
    static string encryptionTheString(string data, char key);
};

#endif // CHATCONTROL_H
