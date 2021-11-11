//
// Created by kolya on 10/4/2021.
//

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include "TcpConnection.h"
#include "DataRequest.h"

void TcpConnection::start()
{
    startReceive();
    /*
    m_Message = make_daytime_string();

    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(m_Message),
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
    */
}

void TcpConnection::handleWrite(const boost::system::error_code &error, size_t bytes)
{
    if (error != boost::system::error_code())
    {
        spdlog::get("Network")->info("connection closed or something gone wrong");
        return;
    }
    startReceive();
}

void TcpConnection::handleSizeRead(const boost::system::error_code &error, size_t bytes)
{
    if (error != boost::system::error_code())
    {
        spdlog::get("Network")->info("connection closed or something gone wrong");
        return;
    }
    spdlog::get("Network")->info(bytes);
    m_Read.resize(m_SizeReader);
    boost::asio::async_read(m_Socket, boost::asio::buffer(&m_Read[0], m_SizeReader),
                            boost::bind(&TcpConnection::handleRead, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::handleRead(const boost::system::error_code &error, size_t bytes)
{
    if (error != boost::system::error_code())
    {
        spdlog::get("Network")->info("connection closed or something gone wrong");
        return;
    }
    //spdlog::get("Network")->info(m_SizeReader);
    //spdlog::get("Network")->info(m_Read);

    nlohmann::json request = nlohmann::json::parse(m_Read);
    DataRequest request_handle(request, m_HandlerPtr);
   /*
    nlohmann::json test = {
            {"task", {{"name", "myname"}, {"id", 123}}},
            {"description", "this is a task"}
    };
    */
    m_Message = request_handle.GetData().dump();
    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(m_Message),
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
    spdlog::get("Network")->info("Message sent");
}

void TcpConnection::startReceive()
{
    spdlog::get("Network")->info("Waiting for reading");
    boost::asio::async_read(m_Socket, boost::asio::buffer(&m_SizeReader, 4),
                            boost::bind(&TcpConnection::handleSizeRead, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}
