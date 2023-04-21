cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(async_server VERSION 1.0.0 DESCRIPTION "Знакомство с асинхронным вводом/выводом на C++")

set(Boost_ROOT boost_1_82_0)
set(Boost_INCLUDE_DIR Boost/include/boost-1_82)
set(Boost_LIBRARIES_DIR Boost/lib)
link_directories(${Boost_LIBRARIES_DIR})


#include_directories(${CMAKE_SOURCE_DIR}/src)
find_library(Boost PATHS Boost/lib)
message(STATUS ${Boost_LIBRARIES})
add_executable(async_server src/main.cpp)
add_executable(tcp_client src/blocking_tcp_echo_client.cpp)
target_include_directories(tcp_client PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(tcp_client C:\\Users\\Egor\\CLionProjects\\cpp-async\\Boost\\lib\\libboost_system-mgw12-mt-x64-1_82.a)


enable_testing()
if (BUILD_TESTING)
    add_subdirectory(test)
endif ()
