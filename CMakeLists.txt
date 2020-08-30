cmake_minimum_required(VERSION 3.16)

project(Algorithms)
set(CMAKE_CXX_STANDARD 17)

# Add files to sources
set(SRC_FILES main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/HashTable)

add_executable(app ${SRC_FILES})

# install(TARGETS app DESTINATION bin)