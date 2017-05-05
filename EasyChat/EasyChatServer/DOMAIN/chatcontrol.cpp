#include "chatcontrol.h"
using namespace std;
chatControl::chatControl()
{

}



string chatControl::login(string account, string password)
{
    Account ac;
    int ret;
    string pwd;
    Json::FastWriter fastWriter;
    Json::Value result;

    if (ac.IsAccountExist(account))
    {
        pwd = ac.getPassword(account);
        if (password == pwd)
            ret =EC_LOGIN_RESULT_SUCCESSFUL;
        else
            ret = EC_LOGIN_RESULT_WRONG_PASSWORD;
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

string chatControl::registerAccount(string password, string nickname, string sex, string age)
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

string chatControl::findAccountInfo(string account)
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

vector<string> chatControl::getLinkmanList(string account)
{

    linkman_linkmanGroup ll;
    vector<string> ret;

    ret = ll.getAllLinkmanInformation(account);
    return ret;
}

string chatControl::createGroup(string groupName, string groupOwner)
{
    group gp;
    string ret;
    Json::FastWriter fastWriter;
    Json::Value result;

    ret =gp.addGroup(groupName,groupOwner);

    result["purpose"] = 8;
    result["account"] = ret;
    std::string jsonStr = fastWriter.write(result);
    return jsonStr;
}

// 待完成
string chatControl::getOfflineMessage(string account)
{
    offlineMessage msg;
    vector<QString> ret;
    Json::FastWriter fastWriter;
    Json::Value result;

    //ret = msg.getOfflineMessage(account);
    return "ok";
}

string chatControl::encryptionTheString(string data, char key)
{

        string res;
        for(auto &var : data)
        {
            res += var ^ key;
        }
        return res;
}
