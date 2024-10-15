cmake_minimum_required(VERSION 3.27)
project(eksamen_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(SOURCE_FILES main.cpp)

# Set this path to your Qt 6 installation
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.1/mingw_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Adjust for Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(eksamen_qt main.cpp)
target_link_libraries(eksamen_qt Qt6::Widgets)
