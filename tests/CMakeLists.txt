
set(elastic_TEST_FILES
    // "ContextTests.cpp"
)

add_executable(elasticTests ${elastic_TEST_FILES})
target_link_libraries(elasticTests elastic testing)
set_property(TARGET elasticTests PROPERTY FOLDER elastic)
