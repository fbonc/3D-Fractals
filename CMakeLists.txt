cmake_minimum_required(VERSION 3.5)
project(NEA VERSION 1.0.0)

add_executable(NEA src/config.h src/main.cpp)

target_include_directories(NEA PRIVATE dependencies)

target_link_libraries(NEA glfw)