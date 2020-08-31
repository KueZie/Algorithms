cmake_minimum_required(VERSION 3.17)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(HashTable)

add_executable(Algorithms
        HashTable/HashTable.h
        HashTable/HashTableEntry.h
        main.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Algorithms PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Algorithms PUBLIC DEBUG=0)
endif()