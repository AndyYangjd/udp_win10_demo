cmake_minimum_required(VERSION 3.23)
project(udp_server_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(udp_server udp_server.cpp)

add_executable(udp_client udp_client.cpp)
