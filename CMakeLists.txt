cmake_minimum_required(VERSION 3.20)
project(fractals LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/external/glad/glad.c"
    "${CMAKE_SOURCE_DIR}/external/dearimgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/external/dearimgui/backends/imgui_impl_glfw*.cpp"
    "${CMAKE_SOURCE_DIR}/external/dearimgui/backends/imgui_impl_opengl3*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/external/Eigen"
    "${CMAKE_SOURCE_DIR}/external/glad"
    "${CMAKE_SOURCE_DIR}/external/KHR"
    "${CMAKE_SOURCE_DIR}/external/"
    "${CMAKE_SOURCE_DIR}/external/dearimgui"
    "${CMAKE_SOURCE_DIR}/external/dearimgui/backends"
    "${CMAKE_SOURCE_DIR}/external/GLFW"
)


find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()
