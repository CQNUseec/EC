#ifndef SERVER_H
#define SERVER_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/error.hpp>
#include <memory>
#include <boost/bind.hpp>
#include <iostream>
#include <jsoncpp/json.h>
#include "DOMAIN/ecglobal.h"
#include "DOMAIN/chatcontrol.h"

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::placeholders;
using namespace boost::system;  //error_code
class Server
{
    typedef Server this_type;
    typedef ip::tcp::acceptor acceptor_type;
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;
    typedef boost::shared_ptr<socket_type> sock_ptr;
    typedef boost::system::error_code error_code;
    typedef vector<char> buffer_type;
    typedef ip::address address_type;
public:
    Server();
    void run();
    void accept();
    void accept_handler(const error_code &ec,sock_ptr sock);
    void read_handler(const error_code& ec,sock_ptr sock);
    void setPtr(std::shared_ptr<ChatControl> ptr);

private:
    //登录
    void login_handler(const error_code&ec,sock_ptr sock,Json::Value root);

    //注册
    void register_handler(const error_code &ec,sock_ptr sock,Json::Value root);

    //获取好友列表
    void getFriendList_handler(const error_code &ec,sock_ptr sock,Json::Value root);

    //查找帐号信息
    void findAccount_handler(const error_code &ec,sock_ptr sock,Json::Value root);

    //发送消息（工具函数，可重用）
    void sendMessage(const error_code &ec, string receiver, string msg);

    //发送离线消息
    void sendOfflineMessage(const error_code &ec, string receiver, vector<string> msgs);

    //请求添加好友
    void requestAddFriend(const error_code &ec, string receiver,string message);

    //同意添加好友
    void agreeAddFriend_handler(const error_code &ec,sock_ptr sock,Json::Value root);

    //发送消息
    void sendMessage_handler(const error_code &ec,string sender,string receiver, string message);

    //注销
    void logout_handler(const error_code &ec,Json::Value root);

    //列出群聊组
    void listGroup_handler(const error_code &ec,sock_ptr sock,Json::Value root);

    //
    void listGroupMembers_handler(const error_code &ec,string account);


private:
    io_service                    m_io;
    acceptor_type                 m_acceptor;
    buffer_type                   m_buf;
    string                        m_result_str;
private:
    std::shared_ptr<ChatControl> chat_ptr;
};


#endif // SERVER_H
