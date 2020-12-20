cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(TESTING ON)
    enable_testing()
else()
    set(TESTING OFF)
endif()

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(vendors/googletest)
