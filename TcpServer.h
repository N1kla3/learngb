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
    explicit TcpServer(boost::asio::io_service& ioService);

private:
    void startAccept();

    void handleAccept(TcpConnection::pointer newConnection, const boost::system::error_code& error);

    boost::asio::ip::tcp::acceptor m_Acceptor;
};


