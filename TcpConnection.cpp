//
// Created by kolya on 10/4/2021.
//

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
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
    return;
    spdlog::get("Network")->info("message sent");
    nlohmann::json test = {
            {"task", {{"name", "myname"}, {"id", 123}}},
            {"description", "this is a task"}
    };
    m_Message = test.dump();
    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(m_Message),
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}
