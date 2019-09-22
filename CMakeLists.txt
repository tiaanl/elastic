cmake_minimum_required(VERSION 3.10.0)

if(TARGET elastic)
    return()
endif()

project(elastic)

# Options

option(ELASTIC_BUILD_EXAMPLES "Build example projects" ON)
set(CMAKE_CXX_STANDARD 14)

# Dependencies

add_subdirectory(../reactor reactor)

# elastic

set(elastic_HEADER_FILES
    "include/elastic/Context.h"
    "include/elastic/Renderer/Font.h"
    "include/elastic/Renderer/Renderer.h"
    "include/elastic/Views/ButtonView.h"
    "include/elastic/Views/ColorView.h"
    "include/elastic/Views/ContextView.h"
    "include/elastic/Views/GroupView.h"
    "include/elastic/Views/ImageView.h"
    "include/elastic/Views/LabelView.h"
    "include/elastic/Views/LinearSizerView.h"
    "include/elastic/Views/StackedSizerView.h"
    "include/elastic/Views/View.h"
    )

set(elastic_SOURCE_FILES
    "src/Context.cpp"
    "src/Renderer/Font.cpp"
    "src/Renderer/Renderer.cpp"
    "src/Views/ButtonView.cpp"
    "src/Views/ColorView.cpp"
    "src/Views/ContextView.cpp"
    "src/Views/GroupView.cpp"
    "src/Views/ImageView.cpp"
    "src/Views/LabelView.cpp"
    "src/Views/LinearSizerView.cpp"
    "src/Views/StackedSizerView.cpp"
    "src/Views/View.cpp"
    )

add_library(elastic STATIC ${elastic_HEADER_FILES} ${elastic_SOURCE_FILES})
target_link_libraries(elastic canvas silhouette)
target_include_directories(elastic PUBLIC "${elastic_SOURCE_DIR}/include")
set_property(TARGET elastic PROPERTY FOLDER elastic)

add_subdirectory(tests elastic_tests)

if(ELASTIC_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
