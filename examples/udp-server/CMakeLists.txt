cmake_minimum_required(VERSION 3.14)

project(udp-server)

set(CMAKE_CXX_STANDARD 11)

add_executable(udp-server main.cpp)

target_link_libraries (udp-server LINK_PUBLIC netutils)