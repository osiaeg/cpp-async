cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(async_server_client VERSION 1.0.0 DESCRIPTION "Знакомство с асинхронным вводом/выводом на C++")

add_executable(async_client src/client.cpp)
add_executable(async_server src/server.cpp)

enable_testing()
if (BUILD_TESTING)
    add_subdirectory(test)
endif ()
