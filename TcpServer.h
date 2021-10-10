//
// Created by kolya on 10/4/2021.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include "TcpConnection.h"

class DataHandler;

class TcpServer
{
public:
    explicit TcpServer(boost::asio::io_service& ioService, const std::shared_ptr<DataHandler>& handler);

private:
    void startAccept();

    void handleAccept(TcpConnection::pointer newConnection, const boost::system::error_code& error);

    boost::asio::ip::tcp::acceptor m_Acceptor;
    boost::asio::io_context m_Context;

    std::shared_ptr<DataHandler> m_HandlerPtr;
};


