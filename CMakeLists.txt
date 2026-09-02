# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.12)

project(Tex CXX)

add_executable(Tex)
target_sources(
    Tex
    PRIVATE
    src/main.cpp
    src/editor.cpp
)

target_include_directories(Tex PRIVATE include)