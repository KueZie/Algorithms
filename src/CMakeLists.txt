set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

if(TESTING)
    target_compile_definitions(${BINARY}_run PUBLIC ENABLE_TESTING)
    target_link_libraries(${BINARY}_run PUBLIC ${CMAKE_PROJECT_NAME}_vendors gtest)
endif()

add_library(${BINARY}_vendors STATIC ${SOURCES})