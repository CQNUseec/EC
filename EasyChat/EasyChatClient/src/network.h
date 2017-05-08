#ifndef NETWORK_H
#define NETWORK_H
#include <QObject>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/error.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <QString>

using namespace boost;                                    using namespace boost::asio;
using namespace boost::asio::placeholders;                using namespace boost::system;
using std::cout;                                          using std::endl;
using std::string;                                        using std::vector;

class NetWork : public QObject
{
    Q_OBJECT
    typedef   NetWork                             this_type;
    typedef   ip::tcp::acceptor                   acceptor_type;
    typedef   ip::tcp::endpoint                   endpoint_type;
    typedef   ip::address                         address_type;
    typedef   ip::tcp::socket                     socket_type;
    typedef   boost::shared_ptr<socket_type>      sock_ptr;
    typedef   vector<char>                        buffer_type;
    typedef boost::system::error_code             error_code;
public:
    NetWork(string ip, int port);
    void accept();
    void sendMessageAndReceiver(string data);
    void sendMessageOnly(string data);
signals:
    void sig_messageFromServer(QString data);
private:
    io_service                           m_io;
    io_service                           m_anathorIo;
    buffer_type                          m_buf;
    buffer_type                          m_chatBuf;
    endpoint_type                        m_ep;
    acceptor_type                        m_acceptor;
};


#endif // NETWORK_H
