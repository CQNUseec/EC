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
public:
    Server();
    void run();
    void accept();
    void accept_handler(const error_code &ec,sock_ptr sock);
    void read_handler(const error_code& ec,sock_ptr sock);
    void sendRequestAddfriend(const error_code& ec, sock_ptr sock);
    void setPtr(std::shared_ptr<chatControl> ptr);
private:
    io_service                    m_io;
    acceptor_type                 m_acceptor;
    buffer_type                   m_buf;
    string                        m_result_str;

private:
    std::shared_ptr<chatControl> chat_ptr;
};


#endif // SERVER_H
