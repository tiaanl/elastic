
set(HIVE_ROOT_DIR "../hive" CACHE PATH "Hive source root directory")
if(NOT HIVE_ROOT_DIR)
    message(FATAL_ERROR "HIVE not found. Please set HIVE_ROOT_DIR.")
endif()

add_subdirectory("${HIVE_ROOT_DIR}" "hive")
