
include(CMakeParseArguments)

macro(ADD_ELASTIC_EXAMPLE EXAMPLE_NAME)
    cmake_parse_arguments(THIS "" "" "SOURCES" ${ARGN})

    nucleus_add_executable(${EXAMPLE_NAME} WIN32 ${THIS_SOURCES})
    target_link_libraries(${EXAMPLE_NAME} elastic canvas)
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER elastic)
endmacro()

add_subdirectory("ElasticDemo")
