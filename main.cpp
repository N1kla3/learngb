#include <iostream>
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "boost/asio.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/asio/ts/io_context.hpp"

int main()
{
    boost::asio::io_context context;
    nlohmann::json a;
    auto console = spdlog::stdout_color_mt("console");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
