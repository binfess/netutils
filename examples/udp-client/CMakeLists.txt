cmake_minimum_required(VERSION 3.14)

project(udp-client)

set(CMAKE_CXX_STANDARD 11)

add_executable(udp-client main.cpp)

target_link_libraries (udp-client LINK_PUBLIC netutils)