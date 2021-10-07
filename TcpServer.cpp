//
// Created by kolya on 10/4/2021.
//

#include "TcpServer.h"

void TcpServer::handleAccept(TcpConnection::pointer newConnection, const boost::system::error_code &error)
{
    if (!error)
    {
        newConnection->start();
    }

    startAccept();
}

void TcpServer::startAccept()
{
    TcpConnection::pointer newConnection = TcpConnection::create((boost::asio::io_context&)m_Acceptor.get_executor().context());
}

TcpServer::TcpServer(boost::asio::io_service &ioService)
        : m_Acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8888))
{
    startAccept();
}