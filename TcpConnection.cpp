//
// Created by kolya on 10/4/2021.
//

#include <spdlog/spdlog.h>
#include "TcpConnection.h"

void TcpConnection::start()
{
    m_Message = make_daytime_string();

    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(m_Message),
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytes)
{
    spdlog::get("Network")->info("message sent");
}
