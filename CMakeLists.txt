cmake_minimum_required(VERSION 3.20)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp arduino_server_Stat.cc arduino_server_Stat.h)
add_subdirectory(third_party/drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
