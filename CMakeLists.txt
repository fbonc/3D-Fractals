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
    "${CMAKE_SOURCE_DIR}/external/Eigen"
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
    OpenGL::GL
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()
