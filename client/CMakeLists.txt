cmake_minimum_required(VERSION 3.14..3.17)

project(client LANGUAGES CXX)

add_executable(run.o main.cpp)

add_library(telnet_client client.cpp)
add_library(command command.cpp)
add_library(command_executor command_executor.cpp)
add_library(client_info client_info.cpp)

target_link_libraries(run.o telnet_client)
target_link_libraries(run.o command)
target_link_libraries(run.o command_executor)
target_link_libraries(run.o client_info)
target_link_libraries(run.o ssl)
target_link_libraries(run.o crypto)
