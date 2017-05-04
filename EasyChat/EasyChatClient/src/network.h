#ifndef NETWORK_H
#define NETWORK_H
#include <QObject>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/error.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace boost;                                    using namespace boost::asio;
using namespace boost::asio::placeholders;                using namespace boost::system;
using std::cout;                                          using std::endl;
using std::string;                                        using std::vector;

class NetWork : public QObject
{
    Q_OBJECT
    typedef   NetWork                             this_type;
    typedef   ip::tcp::endpoint                   endpoint_type;
    typedef   ip::address                         address_type;
    typedef   ip::tcp::socket                     socket_type;
    typedef   boost::shared_ptr<socket_type>      sock_ptr;
    typedef   vector<char>                        buffer_type;
    typedef boost::system::error_code             error_code;
public:
    NetWork(string ip, int port);
    void run();
    void start();
    void sendMessage(string data);
    void read_handler(const error_code& ec, sock_ptr sock);
signals:
    void sig_messageFromServer(string data);
private:
    io_service                           m_io;
    buffer_type                          m_buf;
    endpoint_type                        m_ep;
};


#endif // NETWORK_H