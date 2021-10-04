//
// Created by kolya on 10/4/2021.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include "TcpConnection.h"

class TcpServer
{
public:
    TcpServer(boost::asio::io_service& ioService)
        : m_Acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
    {
        startAccept();
    }

private:
    void startAccept()
    {
        TcpConnection::pointer newConnection = TcpConnection::create(m_Acceptor.get_executor());
    }

    void handleAccept(TcpConnection::pointer newConnection, const boost::system::error_code& error);

    boost::asio::ip::tcp::acceptor m_Acceptor;
};


