cmake_minimum_required(VERSION 3.5)
project(NEA VERSION 1.0.0)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/felip/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)

add_executable(NEA src/config.h 
    src/main.cpp
    src/glad.c)

target_include_directories(NEA PRIVATE dependencies)

target_link_libraries(NEA glfw OpenGL::GL)