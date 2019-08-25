cmake_minimum_required(VERSION 3.14)

project(netutils VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )

add_library(netutils STATIC ${SOURCES})

target_include_directories (netutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(netutils PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        )

install(TARGETS netutils
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

add_subdirectory(examples/udp-client)
add_subdirectory(examples/udp-server)
