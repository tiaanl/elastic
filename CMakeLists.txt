cmake_minimum_required(VERSION 3.10.0)

project(elastic)

option(ELASTIC_BUILD_EXAMPLES "Build example projects" ON)

add_subdirectory(../canvas canvas)
add_subdirectory(../silhouette silhouette)

file(GLOB_RECURSE elastic_HEADER_FILES include/**.h)
file(GLOB_RECURSE elastic_SOURCE_FILES src/**.cpp)

nucleus_add_library(elastic STATIC ${elastic_HEADER_FILES} ${elastic_SOURCE_FILES})
target_link_libraries(elastic PUBLIC canvas silhouette)

add_subdirectory(tests elastic_tests)

if (ELASTIC_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif ()
