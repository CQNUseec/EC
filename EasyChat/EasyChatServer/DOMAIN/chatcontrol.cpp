#include "chatcontrol.h"
#include "DB/account_terminal.h"
using namespace std;
ChatControl::ChatControl()
{

}



string ChatControl::login(string account, string password)
{
    Account ac;

    int ret;
    string pwd;
    Json::FastWriter fastWriter;
    Json::Value result;

    account_terminal at;



    if (ac.isAccountExist(account))
    {
        if(at.isOnline(QString::fromStdString(account)))
        {
            ret = EC_LOGIN_RESULT_ONLINE;
        }
        else
        {
            pwd = ac.getPassword(account);
            if (password == pwd)
                ret =EC_LOGIN_RESULT_SUCCESSFUL;
            else
                ret = EC_LOGIN_RESULT_WRONG_PASSWORD;
        }
    }
    else
        ret = EC_LOGIN_RESULT_INVALID_ACCOUNT;

    result["purpose"] = EC_NETWORK_LOGIN;
    result["result"] = ret;
    std::string jsonStr = fastWriter.write(result);
    //jsonStr = encryptionTheString(jsonStr,'w');
    cout << jsonStr <<endl;
    return jsonStr;
}

string ChatControl::registerAccount(string password, string nickname, string sex, string age)
{
    Account ac;
    string ret;
    Json::FastWriter fastWriter;
    Json::Value result;

    ret = ac.addAcountInformation(password,nickname,sex,age);

    result["purpose"] = EC_NETWORK_REGISTER;
    result["account"] = ret;
    std::string jsonStr = fastWriter.write(result);
    return jsonStr;
}

string ChatControl::findAccountInfo(string account)
{
    Account ac;
    vector<string> ret;
    Json::FastWriter fastWriter;
    Json::Value result;

    ret = ac.getAccountInformation(account);

    if(ret.size())
    {
        result["purpose"] = EC_NETWORK_FIND_ACCOUNT;
        result["result"] = "ok";
        result["account"] = ret[0];
        result["nickname"] = ret[1];
        result["sex"] = ret[2];
        result["age"] = ret[3];
    }
    else
    {
        result["purpose"] = EC_NETWORK_FIND_ACCOUNT;
        result["result"] = "invalid";
    }

    std::string jsonStr = fastWriter.write(result);
    return jsonStr;
}

vector<string> ChatControl::getLinkmanList(string account)
{
    linkman_linkmanGroup ll;
    vector<string> ret;

    ret = ll.getAllLinkmanInformation(account);
    return ret;
}

string ChatControl::getALinkmanInfo(string account, string linkmanAccount)
{
    linkman_linkmanGroup ll;
    string ret;
    ret = ll.getALinkmanInfo(QString::fromStdString(account),QString::fromStdString(linkmanAccount));
    return ret;
}

string ChatControl::createGroup(string groupName, string groupOwner)
{
    Group gp;
    string ret;
    Json::FastWriter fastWriter;
    Json::Value result;

    ret =gp.addGroup(groupName,groupOwner);

    result["purpose"] = 8;
    result["account"] = ret;
    std::string jsonStr = fastWriter.write(result);
    return jsonStr;
}

vector<string> ChatControl::getGroupList(string account)
{
    group_linkman gl;
    vector<string> ret;
    ret = gl.getAccountAllGroup(QString::fromStdString(account));
    return ret;
}


vector<string> ChatControl::getOfflineMessage(string account)
{
    cout << "get offlineMessage"<<endl;
    OfflineMessage msg;
    vector<string> ret;

    ret = msg.getOfflineMessage(QString::fromStdString(account));

    return ret;
}

bool ChatControl::addOnlineFlag(string account, string flag)
{
    account_terminal at;
    bool ret = at.addflag(QString::fromStdString(account),QString::fromStdString(flag));
    return ret;
}

bool ChatControl::deleteOnlineFlag(string account)
{
    account_terminal at;
    bool ret = at.deleteflag(QString::fromStdString(account));

    return ret;
}

bool ChatControl::IsOnline(string account)
{
    account_terminal at;
    bool ret = at.isOnline(QString::fromStdString(account));
    return ret;
}

string ChatControl::getAccountTerminalFlag(string account)
{
    cout << "get client "<<account<<"  ip:";
    account_terminal at;
    string ret;
    ret = at.getflag(QString::fromStdString(account));
    cout << ret<<endl;
    return ret;
}

bool ChatControl::IsExistOfflineMessage(string account)
{
    OfflineMessage im;
    bool ret = im.IsExistOfflineMessage(QString::fromStdString(account));
    return ret;
}

bool ChatControl::addOfflineMessage(string account, string message)
{
    OfflineMessage omsg;
    if(omsg.addOfflineMessage(QString::fromStdString(account),QString::fromStdString(message)))
        return true;
    else
        return false;
}

bool ChatControl::deleteOfflineMessage(string account)
{
    OfflineMessage msg;
    bool ret =msg.deleteOfflineMessage(QString::fromStdString(account));
    return ret;
}

bool ChatControl::logout(string account)
{
    account_terminal at;
    bool ret = at.deleteflag(QString::fromStdString(account));
    return ret;
}

int ChatControl::agreeAddFriend(string initiated, string aims)
{
    linkman_linkmanGroup ll;
    if(ll.isLinkExist(QString::fromStdString(initiated),QString::fromStdString(aims)))
        return EC_ADDFRIEND_ISFRIEND_ALREADY;
    else
    {
        ll.addLinkmanToLinkmanGroup(QString::fromStdString(initiated),QString::fromStdString(aims),QString::fromStdString("friend"),QString::fromStdString(""));
        ll.addLinkmanToLinkmanGroup(QString::fromStdString(aims),QString::fromStdString(initiated),QString::fromStdString("friend"),QString::fromStdString(""));
        return EC_ADDFRIEND_SUCCESS;
    }
}

bool ChatControl::isGroup(string account)
{
    Group g;
    if(g.IsExsitInDB(account))
        return true;
    else
        return false;
}

vector<string> ChatControl::getGroupAccounts(string account)
{
   group_linkman gl;
   vector<string> ret;
   ret = gl.getAllLinkmanAccount(QString::fromStdString(account));
   return ret;
}

vector<string> ChatControl::getGroupInfo(string account)
{
    cout << "get A group member "<<endl;
    group_linkman gl;
    vector<string> ret;

    ret =gl.getAllLinkmanInfo(QString::fromStdString(account));

    return ret;
}

string ChatControl::encryptionTheString(string data, char key)
{

    string res;
    for(auto &var : data)
    {
        res += var ^ key;
    }
    return res;
}
