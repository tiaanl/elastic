
set(SFML_ROOT_DIR "" CACHE PATH "SFML source root directory")
if(NOT SFML_ROOT_DIR)
  message(FATAL_ERROR "SFML not found. Please set SFML_ROOT_DIR.")
endif()

add_subdirectory("${SFML_ROOT_DIR}" "sfml")

include_directories("${SFML_ROOT_DIR}/include")
#include_directories("${SFML_ROOT_DIR}/src")
