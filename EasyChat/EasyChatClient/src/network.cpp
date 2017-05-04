#include "network.h"
using std::string;

NetWork::NetWork(string ip, int port):m_buf(100, 0), m_ep(address_type::from_string(ip), port)
{
//    start();
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

void NetWork::sendMessage(std::string data)
{
    sock_ptr sock(new socket_type (m_io));
    sock->connect(m_ep);
    for(auto &var : m_buf)
        var = '\0';
    sock->send(buffer(data));
    sock->receive(buffer(m_buf));
    std::string res = &m_buf[0];
    std::cout << res;
    emit sig_messageFromServer(res);
}

void NetWork::read_handler(const NetWork::error_code &ec, NetWork::sock_ptr sock)
{
    if(ec)
        return;
    cout << &m_buf[0] << endl;
    sock->async_read_some(buffer(m_buf),
                          [this, sock] (const error_code& ec, std::size_t)
    {
        read_handler(ec, sock);
    }
                          );
}

