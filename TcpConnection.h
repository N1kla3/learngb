//
// Created by kolya on 10/4/2021.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/bind.hpp"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_service& ioService)
    {
        return pointer(new TcpConnection(ioService));
    }

    boost::asio::ip::tcp::socket& socket()
    {
        return m_Socket;
    }

    void start()
    {
        m_Message = make_daytime_string();

        boost::asio::async_write(m_Socket,
            boost::asio::buffer(m_Message),
            boost::bind(&TcpConnection::handleWrite, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

private:
    TcpConnection(boost::asio::io_service& ioService)
        : m_Socket(ioService)
    {

    }

    void handleWrite(const boost::system::error_code& error, size_t bytes){}

    std::string make_daytime_string()
    {
        using namespace std; // For time_t, time and ctime;
        time_t now = time(0);
        return ctime(&now);
    }

    boost::asio::ip::tcp::socket m_Socket;

    std::string m_Message;
};


