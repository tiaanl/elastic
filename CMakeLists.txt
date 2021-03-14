cmake_minimum_required(VERSION 3.10.0)

project(elastic)

find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(../canvas canvas)
add_subdirectory(../silhouette silhouette)

option(ELASTIC_BUILD_EXAMPLES "Build example projects" ON)

file(GLOB_RECURSE elastic_HEADER_FILES include/**.h)
file(GLOB_RECURSE elastic_SOURCE_FILES src/**.cpp)

nucleus_add_library(elastic STATIC ${elastic_HEADER_FILES} ${elastic_SOURCE_FILES})
target_link_libraries(elastic PUBLIC canvas silhouette)

set(elastic_TEST_FILES
    tests/ContextTests.cpp
    tests/TestsMain.cpp
    )

add_executable(elasticTests ${elastic_TEST_FILES})
target_link_libraries(elasticTests PRIVATE elastic)
target_link_libraries(elasticTests PRIVATE Catch2::Catch2)

if (ELASTIC_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif ()
