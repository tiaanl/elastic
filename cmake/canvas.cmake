
set(CANVAS_ROOT_DIR "../canvas" CACHE PATH "Canvas source root directory")
if(NOT CANVAS_ROOT_DIR)
    message(FATAL_ERROR "CANVAS not found. Please set CANVAS_ROOT_DIR.")
endif()

add_subdirectory("${CANVAS_ROOT_DIR}" "nucleus")
