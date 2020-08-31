cmake_minimum_required(VERSION 3.17)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algorithms
        containers/hash_table/HashTable.h
        containers/hash_table/HashTableEntry.h
        main.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Algorithms PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Algorithms PUBLIC DEBUG=0)
endif()