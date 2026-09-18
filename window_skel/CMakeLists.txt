cmake_minimum_required(VERSION 3.20)

project(WindowSkeleton LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(window_skel
    source/main.cpp
    source/window.cpp
    source/renderer.cpp
    source/texture_display.cpp
)

target_include_directories(window_skel PRIVATE
    include
)

target_link_libraries(window_skel PRIVATE
    glfw
    GLEW::GLEW
    OpenGL::GL
)