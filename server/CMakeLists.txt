cmake_minimum_required(VERSION 3.14..3.17)

project(client LANGUAGES CXX)

add_executable(run.o main.cpp)

add_library(server_socket server_socket.cpp)
add_library(ssl_server_socket ssl_server_socket.cpp)
add_library(command command.cpp)

target_link_libraries(run.o ssl)
target_link_libraries(run.o crypto)
target_link_libraries(run.o command)
target_link_libraries(run.o ssl_server_socket)
target_link_libraries(run.o server_socket)
