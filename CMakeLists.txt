cmake_minimum_required(VERSION 2.8.7)
project("elastic")

# General options

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

# Dependencies

include("cmake/sfml.cmake")
include("cmake/nucleus.cmake")

# Options

# If nucleus unit tests are enabled, then we can enable our own unit tests.
if(NUCLEUS_BUILD_UNITTESTS)
  option(ELASTIC_BUILD_TESTS "Build unittests with library?")
endif()

option(ELASTIC_BUILD_EXAMPLES "Build example projects")

# elastic

include_directories("include")

set("elastic_INCLUDE_FILES"
  "include/elastic/context.h"
  "include/elastic/resources/resource_loader.h"
  "include/elastic/resources/resource_store.h"
  "include/elastic/views/button_view.h"
  "include/elastic/views/color_view.h"
  "include/elastic/views/context_view.h"
  "include/elastic/views/group_view.h"
  "include/elastic/views/linear_sizer_view.h"
  "include/elastic/views/stacked_sizer_view.h"
  "include/elastic/views/text_view.h"
  "include/elastic/views/view.h"
)

set("elastic_SOURCE_FILES"
  "src/context.cpp"
  "src/views/button_view.cpp"
  "src/views/color_view.cpp"
  "src/views/context_view.cpp"
  "src/views/group_view.cpp"
  "src/views/linear_sizer_view.cpp"
  "src/views/stacked_sizer_view.cpp"
  "src/views/text_view.cpp"
  "src/views/view.cpp"
)

if(ELASTIC_BUILD_TESTS)
  set("elastic_TEST_FILES"
    "tests/context_tests.cpp"
  )
endif()

add_library("elastic" STATIC ${elastic_INCLUDE_FILES} ${elastic_SOURCE_FILES})
target_link_libraries("elastic" "nucleus" "sfml-graphics" "sfml-window" "sfml-system")
target_include_directories("elastic" PUBLIC "${elastic_SOURCE_DIR}/include")
set_property(TARGET "elastic" PROPERTY FOLDER "elastic")

if(ELASTIC_BUILD_TESTS)
  add_executable("elastic_tests" ${elastic_TEST_FILES})
  target_link_libraries("elastic_tests" "gtest" "gtest_main" "elastic")
  set_property(TARGET "elastic_tests" PROPERTY FOLDER "elastic")
endif()

if(ELASTIC_BUILD_EXAMPLES)
  add_subdirectory("examples")
endif()
