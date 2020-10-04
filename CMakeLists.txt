
cmake_minimum_required(VERSION 2.6)
project(ion-bibtex)

# Global options for the compiler
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -O3")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/)

# find_package(glibmm REQUIRED)

# There are test cases in all builds
enable_testing()

add_subdirectory(src)


