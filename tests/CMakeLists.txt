
set(elastic_TEST_FILES
    "context_tests.cpp"
)

add_executable("elastic_tests" ${elastic_TEST_FILES})
target_link_libraries("elastic_tests" "googletest" "elastic")
set_property(TARGET "elastic_tests" PROPERTY FOLDER "elastic")
