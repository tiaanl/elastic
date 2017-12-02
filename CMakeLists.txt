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
    "include/elastic/Context.h"
    "include/elastic/Resources/ResourceLoader.h"
    "include/elastic/Resources/ResourceStore.h"
    "include/elastic/Views/ButtonView.h"
    "include/elastic/Views/ColorView.h"
    "include/elastic/Views/ContextView.h"
    "include/elastic/Views/GroupView.h"
    "include/elastic/Views/LabelView.h"
    "include/elastic/Views/LinearSizerView.h"
    "include/elastic/Views/StackedSizerView.h"
    "include/elastic/Views/TextView.h"
    "include/elastic/Views/View.h"
)

set(elastic_SOURCE_FILES
    "src/Context.cpp"
    "src/Views/ButtonView.cpp"
    "src/Views/ColorView.cpp"
    "src/Views/ContextView.cpp"
    "src/Views/GroupView.cpp"
    "src/Views/LabelView.cpp"
    "src/Views/LinearSizerView.cpp"
    "src/Views/StackedSizerView.cpp"
    "src/Views/TextView.cpp"
    "src/Views/View.cpp"
)

add_library(elastic STATIC ${elastic_HEADER_FILES} ${elastic_SOURCE_FILES})
target_link_libraries(elastic nucleus canvas)
target_include_directories(elastic PUBLIC "${elastic_SOURCE_DIR}/include")
set_property(TARGET elastic PROPERTY FOLDER elastic)

add_subdirectory(tests elastic_tests)

if(ELASTIC_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
