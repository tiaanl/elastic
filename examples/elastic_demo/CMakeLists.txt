add_subdirectory(../../../silhouette silhouette)

nucleus_add_executable(ElasticDemo WIN32 elastic_demo.cpp)
target_link_libraries(ElasticDemo PRIVATE elastic silhouette)
set_property(TARGET ElasticDemo PROPERTY FOLDER elastic)
