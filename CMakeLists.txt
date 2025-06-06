cmake_minimum_required(VERSION 3.0)
project(tm VERSION 0.1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add the executable
add_executable(tm main.cpp)

target_compile_definitions(tm PRIVATE TM_VERSION="${PROJECT_VERSION}")


