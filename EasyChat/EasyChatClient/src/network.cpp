#include "network.h"
#include <iostream>
#include <boost/thread.hpp>
using std::string;

NetWork::NetWork(string ip, int port):m_buf(100, 0), m_chatBuf(100,0),
    m_ep(address_type::from_string(ip), port),
    m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 6677))
{

}

void NetWork::accept()
{
    io_service io;
    ip::udp::socket sock(io, ip::udp::endpoint(ip::udp::v4(), 6677));
    while(true)
    {
        vector<char> buf(200, 0);
        ip::udp::endpoint ep;
        error_code ec;
        sock.receive_from(buffer(buf), ep, 0, ec);
        std::string tmp = &buf[0];
        emit sig_messageFromServer(QString::fromStdString(tmp));
        for(auto &var: buf)
            var = '\0';
        std::cout << tmp << std::endl;
    }
}

void NetWork::sendMessageOnly(std::string data)
{
    sock_ptr sock(new socket_type (m_io));
    sock->connect(m_ep);
    sock->send(buffer(data));
}

void NetWork::sendMessageAndReceiver(std::string data)
{
    sock_ptr sock(new socket_type (m_io));
    sock->connect(m_ep);
    for(auto &var : m_buf)
        var = '\0';
    sock->send(buffer(data));
    sock->receive(buffer(m_buf));
    std::string res = &m_buf[0];
    for(auto &var : m_buf)
        var = '\0';
    std::cout << res << std::endl;
    if(res == "friendList" || res == "groupList" || res == "groupMembers")
    {
        vector<char> tempBuf(200, 0);
        sock->receive(buffer(tempBuf));
        std::string data = &tempBuf[0];
        while( data != "end")
        {
            std::cout << data << std::endl;
            emit sig_messageFromServer(QString::fromStdString(data));
            sock->send(buffer("temp"));
            for(auto &var : tempBuf)
                var = '\0';
            sock->receive(buffer(tempBuf));
            data = &tempBuf[0];
        }
    }
    else
        emit sig_messageFromServer(QString::fromStdString(res));
}


