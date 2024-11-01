cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pelvi)

find_package(Qt6 6.8 REQUIRED COMPONENTS
        Sql
)

qt6_add_library(pelvi SHARED
        src/database.cpp
        src/pelvi.cpp
        src/dbinit.cpp
        include/database.h
        include/pelvi.h
        include/dbinit.h
)

target_include_directories(pelvi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pelvi PRIVATE Qt6::Sql)
