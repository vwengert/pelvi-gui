# pelvi/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(pelvi)

add_library(pelvi STATIC
        src/pelvi.cpp
        include/pelvi.h
)

target_include_directories(pelvi PUBLIC include)