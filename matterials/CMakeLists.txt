cmake_minimum_required(VERSION 3.20)

project(model_experiments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(render
    src/main.cpp
)

target_include_directories(render PRIVATE
    include
)