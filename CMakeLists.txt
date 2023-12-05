cmake_minimum_required(VERSION 3.25)
project(UIUC_CS128)

set(CMAKE_CXX_STANDARD 17)

add_executable(UIUC_CS128 main.cpp)
add_executable(MP-3 MP-3.cpp cord.hpp shared_pointer.hpp cord_utilities.hpp cord.cpp shared_pointer.cpp cord_utilities.cpp)