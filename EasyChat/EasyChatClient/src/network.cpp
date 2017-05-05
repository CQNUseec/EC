#include "network.h"
#include <iostream>
using std::string;

NetWork::NetWork(string ip, int port):m_buf(100, 0), m_chatBuf(100,0),
    m_ep(address_type::from_string(ip), port),
    m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 6677))
{
    accept();
}

void NetWork::run()
{
    m_io.run();
}

void NetWork::start()
{
    sock_ptr sock(new socket_type (m_io));
    sock->async_connect(m_ep,
                        [this, sock] (const error_code& ec)
    {
        if(ec)
            return;
        sock->async_read_some(buffer(m_buf),
                              [this, sock] (const error_code& ec, std::size_t)
        {
            read_handler(ec, sock);
        }
        );
    }
    );
}

void NetWork::accept()
{
    sock_ptr sock(new socket_type(m_io));
    m_acceptor.async_accept(
                *sock,
                [this, sock] (const error_code& ec)
    {
        if(ec)
            return;
        {
            cout << "receive message." << endl;
            sock->async_read_some(buffer(m_chatBuf),
                                  [this, sock] (const error_code& ec, std::size_t)
            {
                read_handler(ec, sock);
            }
            );
        }
        accept();        //再次启动异步接受连接
    }
    );
}

void NetWork::sendMessageOnly(std::__cxx11::string data)
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
    std::cout << res << std::endl;
    if(res == "friendList")
    {
        vector<char> tempBuf(100, 0);
        sock->receive(buffer(tempBuf));
        std::string data = &tempBuf[0];
        while( data != "end")
        {
            std::cout << data << std::endl;
            emit sig_messageFromServer(data);
            sock->send(buffer("temp"));
            for(auto &var : tempBuf)
                var = '\0';
            sock->receive(buffer(tempBuf));
            data = &tempBuf[0];
        }
    }
    else
        emit sig_messageFromServer(res);
}

void NetWork::read_handler(const NetWork::error_code &ec, NetWork::sock_ptr sock)
{
    if(ec)
        return;
    std::string res = &m_chatBuf[0];
    cout << &m_chatBuf[0] << endl;
    emit sig_messageFromServer(res);

    //    sock->async_read_some(buffer(m_chatBuf),
    //                          [this, sock] (const error_code& ec, std::size_t)
    //    {
    //        read_handler(ec, sock);
    //    }
    //    );
}

