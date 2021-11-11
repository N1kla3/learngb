#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "boost/asio.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "TcpServer.h"
#include "DataHandler.h"

int main()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt"));
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    auto NetworkLog = std::make_shared<spdlog::logger>("Network", begin(sinks), end(sinks));
    auto CoreLog = std::make_shared<spdlog::logger>("Core", begin(sinks), end(sinks));
    spdlog::register_logger(NetworkLog);
    spdlog::register_logger(CoreLog);
    spdlog::set_pattern("[%D %H:%M:%S %z][thread %t]%^[%n][%l]%v%$");

    CoreLog->info("---------- App Started ----------");

    boost::asio::io_context context;

    try
    {
        boost::asio::io_service service;
        TcpServer server(service, std::make_shared<DataHandler>());
        service.run();
    }
    catch (std::exception& e)
    {
        CoreLog->error(e.what());
    }

    CoreLog->info("========== App Finished ==========");
    return 0;
}
