set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(TEST_SOURCES ${TEST_SOURCES})

add_executable(${BINARY}_tests ${TEST_SOURCES})

if(TESTING)
    target_compile_definitions(${BINARY}_tests PUBLIC ENABLE_TESTING)
    target_link_libraries(${BINARY}_tests PUBLIC ${CMAKE_PROJECT_NAME}_vendors gtest)
endif()