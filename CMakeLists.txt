cmake_minimum_required(VERSION 2.8.7)

project("elastic")

# Dependencies

include("cmake/canvas.cmake")

# Compiler options

include(${NUCLEUS_ROOT_DIR}/cmake/gcc.cmake)
include(${NUCLEUS_ROOT_DIR}/cmake/msvc.cmake)
include(${NUCLEUS_ROOT_DIR}/cmake/win32.cmake)

# Options

option(ELASTIC_BUILD_EXAMPLES "Build example projects")

# elastic

set(elastic_HEADER_FILES
    "include/elastic/context.h"
    "include/elastic/resources/resource_loader.h"
    "include/elastic/resources/resource_store.h"
    "include/elastic/views/button_view.h"
    "include/elastic/views/ColorView.h"
    "include/elastic/views/context_view.h"
    "include/elastic/views/group_view.h"
    "include/elastic/views/LabelView.h"
    "include/elastic/views/linear_sizer_view.h"
    "include/elastic/views/stacked_sizer_view.h"
    "include/elastic/views/text_view.h"
    "include/elastic/views/view.h"
)

set(elastic_SOURCE_FILES
    "src/context.cpp"
    "src/views/button_view.cpp"
    "src/views/ColorView.cpp"
    "src/views/context_view.cpp"
    "src/views/group_view.cpp"
    "src/views/LabelView.cpp"
    "src/views/linear_sizer_view.cpp"
    "src/views/stacked_sizer_view.cpp"
    "src/views/text_view.cpp"
    "src/views/view.cpp"
)

add_library(elastic STATIC ${elastic_HEADER_FILES} ${elastic_SOURCE_FILES})
target_link_libraries(elastic nucleus canvas)
target_include_directories(elastic PUBLIC "${elastic_SOURCE_DIR}/include")
set_property(TARGET elastic PROPERTY FOLDER elastic)

add_subdirectory(tests elastic_tests)

if (ELASTIC_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif ()
