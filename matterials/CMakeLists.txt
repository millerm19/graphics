cmake_minimum_required(VERSION 3.20)
project(matterials LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)

add_executable(render
    src/main.cpp
    include/outputting/window.cpp
)

target_include_directories(render PRIVATE
    include
    third_party/stb
)

target_link_libraries(render PRIVATE
    glfw
    opengl32
)