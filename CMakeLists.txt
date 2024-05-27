cmake_minimum_required(VERSION 3.0)
project(tm)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add the executable
add_executable(tm main.cpp
        TagManager.cpp
        TagManager.h)

# move executable to current directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

