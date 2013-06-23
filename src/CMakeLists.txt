
# Specifiy a CMake version
cmake_minimum_required(VERSION 2.6)

# This will make the core libraries, including test harnesses
project(CoreLibraries)

# Global options for the compiler
add_definitions("-Wall"  -O3)

# There are test cases in all builds
enable_testing()

#--------------------------------------------------------------------------------------------------
# Set the binay output
# Re-enable when I can get this sorted with make_test
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug CACHE PATH "Single directory for all executables")

#--------------------------------------------------------------------------------------------------


add_subdirectory(Utilities)
add_subdirectory(ION)

