
cmake_minimum_required(VERSION 2.6)
project(ion-bibtex)

# Global options for the compiler
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -O3")


# There are test cases in all builds
enable_testing()

add_subdirectory(src)


