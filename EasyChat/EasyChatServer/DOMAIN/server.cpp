#include "server.h"

//解析json字符串
bool parseJsonString(string jsonStr,Json::Value &root)
{
    Json::Value ret;
    Json::Reader reader;
    if(reader.parse(jsonStr, root))
        return true;
    else
        return false;
}


Server::Server(): m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 6688)),m_buf(512,0)
{
    accept();
}

void Server::run()
{
    m_io.run();
}

void Server::accept()
{
    sock_ptr sock(new socket_type(m_io));
    m_acceptor.async_accept(*sock,bind(&this_type::accept_handler,this,boost::asio::placeholders::error,sock));
}

void Server::accept_handler(const Server::error_code &ec, Server::sock_ptr sock)
{
    if (ec)
        return;
    cout<<"receive from client:"<<sock->remote_endpoint().address()<< endl;
    sock->async_read_some(buffer(m_buf),bind(&this_type::read_handler,this,boost::asio::placeholders::error,sock));
    accept();
}

void Server::read_handler(const Server::error_code &ec, Server::sock_ptr sock)
{

    if(ec)
        return;

    string client_ip = sock->remote_endpoint().address().to_string();
    string temp = &m_buf[0];

    //temp = chatControl::encryptionTheString(temp,'w'); //解密

    for (auto &s:m_buf)  //清空缓冲区
        s = '\0';

    cout << temp <<endl;

    Json::Value root;
    if(parseJsonString(temp,root))
    {
        int purpuse = root["purpose"].asInt();

        switch (purpuse) {
        case EC_NETWORK_LOGIN: //登录
        {
            login_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_REGISTER://注册
        {
            register_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_FIND_ACCOUNT://查找好友
        {
            findAccount_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_FRIEND_LIST://获取好友列表
        {
            getFriendList_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_SEND_MESSAGE://发消息
        {
            string sender = root["sender"].asString();
            string receiver = root["receiver"].asString();
            sendMessage_handler(ec,sender,receiver,temp);
            break;
        }
        case EC_NETWORK_AGREE_ADD_FRIEND://同意添加好友
        {
            agreeAddFriend_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_ADD_FRIEND://请求加好友
        {
            string receiver = root["aims"].asString();
            requestAddFriend(ec,receiver,temp);
            break;
        }
        case EC_NETWORK_GROUP_LIST://列出群聊组
        {
            cout<<"list all group"<<endl;
            listGroup_handler(ec,sock,root);
            break;
        }
        case EC_NETWORK_LOGOUT: //注销
        {
            logout_handler(ec,root);
            break;
        }
            //        case EC_NETWORK_GROUP_CHAT_MEMBER://获取一个组的所有成员具体信息
            //        {
            //            listGroupMembers_handler(ec,sock,root);
            //            break;
            //        }
        default:
            break;
        }
    }
    else
    {
        cout << "parse error"<<endl;
    }
}

void Server::login_handler(const Server::error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    string ret;
    if (ec)
        return;
    string client_ip = sock->remote_endpoint().address().to_string();
    cout << "login"<<endl;
    string account=root["account"].asString();
    string password = root["password"].asString();
    ret = chat_ptr->login(account,password);
    sock->write_some(buffer(ret));

    Json::Value rt;
    if(parseJsonString(ret,rt))
    {

        int rsl = rt["result"].asInt();
        if(rsl == EC_LOGIN_RESULT_SUCCESSFUL) //验证登录成功
        {

            cout << "log success "<< account<<endl;
            chat_ptr->addOnlineFlag(account,client_ip); //添加在线标志
            //            if(chat_ptr->IsExistOfflineMessage(account))//如果存在离线消息，发送离线消息
            //            {

            //                vector<string> msgs = chat_ptr->getOfflineMessage(account);
            //                sendOfflineMessage(ec,account,msgs);
            //                chat_ptr->deleteOfflineMessage(account);
            //            }

        }
    }

    cout << ret <<endl;
}

void Server::register_handler(const Server::error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    string ret;
    if (ec)
        return;
    cout << "register"<<endl;
    string password = root["password"].asString();
    string nickname = root["nickName"].asString();
    string age = root["age"].asString();
    string sex = root["sex"].asString();
    ret = chat_ptr->registerAccount(password,nickname,sex,age);
    cout << ret <<endl;
    sock->write_some(buffer(ret));
}

void Server::getFriendList_handler(const Server::error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    vector<string> ret;
    if (ec)
        return;
    vector<char> buf(10,0);
    cout << "获取好友列表"<<endl;

    string account = root["sender"].asString();
    ret = chat_ptr->getLinkmanList(account);

    if(ret.size())
    {
        sock->write_some(buffer("friendList"));
        for(auto it = ret.begin();it != ret.end();++it)
        {
            cout << "getallfriends"<<*it <<endl;
            sock->write_some(buffer(*it));
            sock->read_some(buffer(buf));

            for (auto &s:m_buf)  //清空缓冲区
                s = '\0';
        }
        sock->write_some(buffer("end"));
    }
    else
    {
        sock->write_some(buffer("end"));
    }

    if(chat_ptr->IsExistOfflineMessage(account))//如果存在离线消息，发送离线消息
    {

        vector<string> msgs = chat_ptr->getOfflineMessage(account);
        sendOfflineMessage(ec,account,msgs);
        chat_ptr->deleteOfflineMessage(account);
    }
    return;
}

void Server::findAccount_handler(const error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    string ret;
    if (ec)
        return;
    cout <<"查找一个账户信息"<<endl;

    string account = root["account"].asString();
    ret = chat_ptr->findAccountInfo(account);
    cout << ret <<endl;
    sock->write_some(buffer(ret));
}

void Server::sendMessage(const Server::error_code &ec, string receiver, string msg)
{
    if (ec)
        return;
    io_service tmp_io;
    string ip =chat_ptr->getAccountTerminalFlag(receiver);

    //    Json::FastWriter fastwriter;
    //    string receiverAccount = receiverIp["receiver"].asString();
    //    string msg = fastwriter.write(receiverIp);
    //    endpoint_type ep(address_type::from_string(ip),6677);
    //    sock_ptr sock(new socket_type(tmp_io));
    //    sock->connect(ep);
    //    cout << "send online message"<<endl;
    //    sock->send(buffer(msg));
    //    io_service io;


    ip::udp::endpoint send_ep(
                ip::address::from_string(ip),6677);
    ip::udp::socket sock(tmp_io);
    sock.open(ip::udp::v4());
    sock.send_to(buffer(msg), send_ep);

}

void Server::sendOfflineMessage(const Server::error_code &ec, string receiver,vector<string> msgs)
{
    cout <<"send offlineMessage"<<endl;
    if (ec)
        return;
    io_service tmp_io;

    string ip =chat_ptr->getAccountTerminalFlag(receiver);

    ip::udp::endpoint send_ep(
                ip::address::from_string(ip),6677);
    ip::udp::socket sock(tmp_io);
    sock.open(ip::udp::v4());
    for(auto &s:msgs)
    {
        cout << "send 1 msg"<<endl;
        sock.send_to(buffer(s), send_ep);
    }
}

void Server::requestAddFriend(const Server::error_code &ec, string receiver, string message)
{
    if (ec)
        return;
    if(chat_ptr->IsOnline(receiver))
        sendMessage(ec,receiver,message);
    else
        chat_ptr->addOfflineMessage(receiver,message);

    return;
}

void Server::agreeAddFriend_handler(const Server::error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    if (ec)
        return;
    string initiated = root["initiated"].asString();
    string aims = root["aims"].asString();

    int ret = chat_ptr->agreeAddFriend(initiated,aims);

    Json::FastWriter fastWriter;
    Json::Value result;

    result["purpose"]=EC_NETWORK_AGREE_ADD_FRIEND;
    result["result"]=ret;
    string jsonStr = fastWriter.write(result);
    sock->write_some(buffer(jsonStr));

    cout << "agree add friend "<<ret <<endl;

    //同意添加好友后更新两者的好友列表
    string friend1 = chat_ptr->getALinkmanInfo(initiated,aims);
    string friend2 = chat_ptr->getALinkmanInfo(aims,initiated);

    cout<< "更新" <<friend1<<endl;
    cout<<" ——更新"<<friend2<<endl;

    sendMessage(ec,initiated,friend1);
    sendMessage(ec,aims,friend2);

    return;
}

void Server::sendMessage_handler(const Server::error_code &ec,string sender,string receiver, string message)
{
    if(ec)
        return;

    if(chat_ptr->isGroup(receiver)) //群聊
    {
        cout << "send group message"<<endl;

        vector<string> result;

        result = chat_ptr->getGroupAccounts(receiver);

        for(auto &s:result)
        {
            if (s == sender) //
                break;
            else
            {
                if(chat_ptr->IsOnline(s))
                {
                    cout<<"send online message"<<endl;
                    sendMessage(ec,s,message);
                }
                else
                {
                    chat_ptr->addOfflineMessage(s,message);
                    cout <<"add offline success"<<endl;
                }
            }
        }
    }
    else //单聊
    {
        if(chat_ptr->IsOnline(receiver))
        {
            cout <<"send online message"<<endl;
            sendMessage(ec,receiver,message);
        }
        else
        {
            chat_ptr->addOfflineMessage(receiver,message);
            cout <<"add offline success"<<endl;
        }
    }
}

void Server::logout_handler(const Server::error_code &ec, Json::Value root)
{
    if (ec)
        return;
    string account = root["account"].asString();
    chat_ptr->logout(account);
    return;
}

void Server::listGroup_handler(const Server::error_code &ec, Server::sock_ptr sock, Json::Value root)
{
    cout<<"list group handler"<<endl;
    if (ec)
        return;
    string sender = root["sender"].asString();
    vector<string> ret;
    vector<char> buf(50,0);
    ret = chat_ptr->getGroupList(sender);

    if(ret.size())
    {
        sock->write_some(buffer("groupList"));
        for(auto it = ret.begin();it != ret.end();++it)
        {
            cout << "A group"<<*it <<endl;
            sock->write_some(buffer(*it));
            sock->read_some(buffer(buf));

            for (auto &s:m_buf)  //清空缓冲区
                s = '\0';
        }
        sock->write_some(buffer("end"));
    }
    else
    {
        sock->write_some(buffer("end"));
    }

    listGroupMembers_handler(ec,sender);
    return;
}

void Server::listGroupMembers_handler(const Server::error_code&ec, string account)
{
    cout<<"list group members"<<endl;
    if (ec)
        return;

    vector<string> groups;
    groups = chat_ptr->getGroupList(account);

    for(auto &group:groups)
    {
        Json::Value root;
        parseJsonString(group,root);

        string g = root["groupAccount"].asString();

        cout << group<<endl;
        vector<string> members = chat_ptr->getGroupInfo(g);

        for(auto &member:members)
        {
            cout<<"a member of"<<member<<endl;
            sendMessage(ec,account,member);
        }
    }

    return;
}

void Server::setPtr(std::shared_ptr<ChatControl> ptr)
{
    chat_ptr = ptr;
}

