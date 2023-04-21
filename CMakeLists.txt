cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(async_server_client VERSION 1.0.0 DESCRIPTION "Знакомство с асинхронным вводом/выводом на C++")

set(BOOST_ROOT "boost_lib")

find_package(Boost 1.82.0 REQUIRED COMPONENTS system)

add_executable(async_client src/client.cpp)
add_executable(async_server src/server.cpp)
target_include_directories(async_client PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(async_client Boost::system)
target_include_directories(async_server PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(async_server Boost::system)

enable_testing()
if (BUILD_TESTING)
    add_subdirectory(test)
endif ()
