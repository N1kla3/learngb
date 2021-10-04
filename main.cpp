#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "boost/asio.hpp"
#include "boost/graph/adjacency_list.hpp"

int main()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt"));
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    auto NetworkLog = std::make_shared<spdlog::logger>("Network", begin(sinks), end(sinks));
    auto CoreLog = std::make_shared<spdlog::logger>("Core", begin(sinks), end(sinks));

    CoreLog->info("---------- App Started ----------");

    boost::asio::io_context context;
    nlohmann::json test = {
            {"task", {{"name", "myname"}, {"id", 123}}},
            {"description", "this is a task"}
    };

    CoreLog->info(test.dump());

    CoreLog->info("========== App Finished ==========");
    return 0;
}
