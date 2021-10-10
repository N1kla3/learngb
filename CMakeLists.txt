cmake_minimum_required(VERSION 3.20)
project(learngb)

set(CMAKE_CXX_STANDARD 20)
set(JSON_BuildTests OFF CACHE INTERNAL "")

SET(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(json)
add_subdirectory(spdlog)

add_executable(learngb main.cpp TcpServer.h TcpServer.cpp TcpConnection.h TcpConnection.cpp DataHandler.cpp DataHandler.h
        DataRequest.h DataRequest.cpp DataLoader.cpp DataLoader.h)

target_link_libraries(learngb PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog Boost::thread Boost::system)
