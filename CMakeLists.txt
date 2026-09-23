cmake_minimum_required(VERSION 3.20)
project(fractals LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
    URL_HASH SHA256=8586084f71f9bde545ee7fa6d00288b264a2b7ac3607b974e54d13e7162c1c72
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    SOURCE_SUBDIR Eigen
)
FetchContent_MakeAvailable(eigen)
add_library(eigen_headers INTERFACE)
add_library(Eigen3::Eigen ALIAS eigen_headers)
target_include_directories(eigen_headers SYSTEM INTERFACE "${eigen_SOURCE_DIR}")

file(GLOB_RECURSE SRC
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})

add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC external)

add_library(imgui STATIC
    external/dearimgui/imgui.cpp
    external/dearimgui/imgui_draw.cpp
    external/dearimgui/imgui_tables.cpp
    external/dearimgui/imgui_widgets.cpp
    external/dearimgui/imgui_impl_glfw.cpp
    external/dearimgui/imgui_impl_opengl3.cpp
)
target_include_directories(imgui
    PUBLIC external/dearimgui external/dearimgui/backends
    PRIVATE external "${glfw_SOURCE_DIR}/include/GLFW"
)
target_link_libraries(imgui PUBLIC glfw)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/external/glad"
    "${CMAKE_SOURCE_DIR}/external/KHR"
    "${CMAKE_SOURCE_DIR}/external/"
    "${CMAKE_SOURCE_DIR}/external/dearimgui"
    "${CMAKE_SOURCE_DIR}/external/dearimgui/backends"
    "${glfw_SOURCE_DIR}/include/GLFW"
)


find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    imgui
    Eigen3::Eigen
    OpenGL::GL
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()
