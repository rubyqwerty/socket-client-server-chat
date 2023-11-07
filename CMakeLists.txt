cmake_minimum_required(VERSION 3.0)
project(client_server_chat)
set(SOURCE main.cpp)

add_library(chat STATIC chat.cpp)
add_library(epoll STATIC epoll.cpp)
add_library(socket STATIC socket.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} chat epoll socket)
