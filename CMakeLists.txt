cmake_minimum_required(VERSION 3.10.0)

project(elastic)

add_subdirectory(../canvas canvas)

option(ELASTIC_BUILD_EXAMPLES "Build example projects" ON)

set(HEADER_FILES
    include/elastic/context.h
    include/elastic/renderer/font.h
    include/elastic/renderer/image.h
    include/elastic/renderer/renderer.h
    include/elastic/utils/margins.h
    include/elastic/views/button_view.h
    include/elastic/views/color_view.h
    include/elastic/views/context_view.h
    include/elastic/views/group_view.h
    include/elastic/views/image_view.h
    include/elastic/views/label_view.h
    include/elastic/views/linear_sizer_view.h
    include/elastic/views/stacked_sizer_view.h
    include/elastic/views/view.h
    )

set(SOURCE_FILES
    src/context.cpp
    src/renderer/font.cpp
    src/renderer/font.cpp
    src/renderer/renderer.cpp
    src/views/button_view.cpp
    src/views/color_view.cpp
    src/views/context_view.cpp
    src/views/group_view.cpp
    src/views/image_view.cpp
    src/views/label_view.cpp
    src/views/linear_sizer_view.cpp
    src/views/stacked_sizer_view.cpp
    src/views/view.cpp
    )

nucleus_add_library(elastic ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(elastic PUBLIC canvas)

set(TEST_FILES
    tests/context_tests.cpp
    )

nucleus_add_executable(elastic_tests ${TEST_FILES})
target_link_libraries(elastic_tests PRIVATE elastic tests_main)

if (ELASTIC_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
