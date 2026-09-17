
cmake_minimum_required(VERSION 3.20)

project(FileFun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(filefun
    source/main.cpp
)

target_link_libraries(filefun PRIVATE
    glfw
    GLEW::GLEW
    OpenGL::GL
)