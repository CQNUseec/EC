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
    string ret;
    if(parseJsonString(temp,root))
    {
        int purpuse = root["purpose"].asInt();

        switch (purpuse) {
        case EC_NETWORK_LOGIN: //验证登录
        {
            cout << "login"<<endl;
            string account=root["account"].asString();
            string password = root["password"].asString();
            ret = chat_ptr->login(account,password);
            cout << ret <<endl;

            sock->write_some(buffer(ret));
            break;
        }
        case EC_NETWORK_REGISTER://注册
        {
            cout << "register"<<endl;
            string password = root["password"].asString();
            string nickname = root["nickname"].asString();
            string age = root["age"].asString();
            string sex = root["sex"].asString();
            ret = chat_ptr->registerAccount(password,nickname,sex,age);
            cout << ret <<endl;
            sock->write_some(buffer(ret));
            break;
        }
        case EC_NETWORK_FIND_ACCOUNT://查找好友
        {
            string account = root["account"].asString();
            ret = chat_ptr->findAccountInfo(account);
            cout << ret <<endl;
            sock->write_some(buffer(ret));
            break;
        }
        case EC_NETWORK_FRIEND_LIST://获取好友列表
        {
            vector<string> ret;

            vector<char> buf(10,0);

            cout << "获取好友列表"<<endl;

            string account = root["sender"].asString();

            ret = chat_ptr->getLinkmanList(account);

            for(auto &s:ret)
                cout << s<<endl;

            if(ret.size())
            {
                sock->write_some(buffer("friendList"));
                for(auto it = ret.begin();it != ret.end();++it)
                {
                    cout << *it <<endl;
                    sock->write_some(buffer(*it));
                    sock->read_some(buffer(buf));

                    for (auto &s:m_buf)  //清空缓冲区
                        s = '\0';
                }

                sock->write_some(buffer("end"));
            }
            else //ondo
            {

            }

            break;
        }

        case 6:
        {

        }
        default:
            break;
        }
    }
    else
    {
        cout << "parse error"<<endl;
    }



}

void Server::sendRequestAddfriend(const Server::error_code &ec, Server::sock_ptr sock)
{


}

void Server::setPtr(std::shared_ptr<chatControl> ptr)
{
    chat_ptr = ptr;
}
