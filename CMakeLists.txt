cmake_minimum_required(VERSION 3.0)
project(tm)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add the executable
add_executable(tm main.cpp)

# Place built binaries in the project root
set_target_properties(tm PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

