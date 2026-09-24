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

add_executable(${PROJECT_NAME}
    src/app_controller.cpp
    src/camera.cpp
    src/camera_controller.cpp
    src/fractal.cpp
    src/fractals.cpp
    src/glfw_manager.cpp
    src/glsl_manager.cpp
    src/main.cpp
    src/scene_renderer.cpp
    src/shader.cpp
    src/shader_manager.cpp
    src/ui_manager.cpp
)

add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC external external/glad)

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

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    FRACTALS_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    imgui
    Eigen3::Eigen
    OpenGL::GL
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()
