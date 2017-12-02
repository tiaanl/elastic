
set(elastic_TEST_FILES
    "ContextTests.cpp"
)

add_executable(ElasticTests ${elastic_TEST_FILES})
target_link_libraries(ElasticTests googletest elastic)
set_property(TARGET ElasticTests PROPERTY FOLDER elastic)
