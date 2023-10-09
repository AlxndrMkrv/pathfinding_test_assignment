cmake_minimum_required(VERSION 3.5)

project(GraphTests VERSION 1.0 LANGUAGES CXX)

# Forbid in-source build
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(SEND_ERROR "In-source building prohibited")
endif()

# Forbid in-source build
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(SEND_ERROR "In-source building prohibited")
endif()


include_directories(Headers)
include_directories(${CMAKE_SOURCE_DIR}/Headers)


add_executable(dfs_nodes_test Sources/GraphTest_DFS.cxx Headers/GraphTest.hxx)
target_link_libraries(dfs_nodes_test PRIVATE graph_static)
add_test(NAME dfs_create_remove_nodes
         COMMAND $<TARGET_FILE:dfs_nodes_test>)

add_executable(dfs_route_test Sources/RouteTest_DFS.cxx Headers/RouteTest.hxx)
target_link_libraries(dfs_route_test PRIVATE graph_static)
add_test(NAME dfs_trace_route COMMAND $<TARGET_FILE:dfs_route_test>)



