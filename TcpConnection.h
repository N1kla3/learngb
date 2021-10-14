//
// Created by kolya on 10/4/2021.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"

class DataHandler;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_service& ioService, const std::shared_ptr<DataHandler>& handler)
    {
        return pointer(new TcpConnection(ioService, handler));
    }

    boost::asio::ip::tcp::socket& socket() { return m_Socket; }

    void start();

private:
    explicit TcpConnection(boost::asio::io_service& ioService, const std::shared_ptr<DataHandler>& handler)
        : m_Socket(ioService)
        , m_HandlerPtr(handler)
    {

    }

    void handleWrite(const boost::system::error_code& error, size_t bytes);
    void handleRead(const boost::system::error_code& error, size_t bytes);
    void handleSizeRead(const boost::system::error_code& error, size_t bytes);
    void startReceive();

    std::string make_daytime_string()
    {
        using namespace std; // For time_t, time and ctime;
        time_t now = time(0);
        return ctime(&now);
    }

    boost::asio::ip::tcp::socket m_Socket;
    std::string m_Message;
    std::string m_Read;
    int32_t m_SizeReader;

    std::weak_ptr<DataHandler> m_HandlerPtr;
};


