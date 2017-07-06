
include(CMakeParseArguments)

macro(ADD_ELASTIC_EXAMPLE EXAMPLE_NAME)
    cmake_parse_arguments(THIS "" "" "SOURCES" ${ARGN})

    add_executable(${EXAMPLE_NAME} WIN32 ${THIS_SOURCES})
    target_link_libraries(${EXAMPLE_NAME} "elastic" "sfml-main" "canvas")
    set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "elastic")
endmacro()

add_subdirectory("minimal")
add_subdirectory("CanvasIntegration")
