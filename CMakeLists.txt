cmake_minimum_required(VERSION 3.16)

project(apppelvi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.8)

add_subdirectory(pelvi)

qt6_add_executable(apppelvi
        main.cpp
)

qt_add_qml_module(apppelvi
        URI pelvigui
        VERSION 1.0
        QML_FILES
        Main.qml
)

target_link_libraries(apppelvi
        PRIVATE Qt6::Quick
        PRIVATE pelvi
)

include(GNUInstallDirs)
install(TARGETS apppelvi
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
