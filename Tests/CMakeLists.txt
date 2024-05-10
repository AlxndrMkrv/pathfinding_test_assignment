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


add_executable(graph_test Sources/GraphTest_DFS.cxx Headers/GraphTest.hxx)
target_link_libraries(graph_test PRIVATE graph_static)
add_test(NAME graph COMMAND $<TARGET_FILE:graph_test>)

add_executable(dfs_tracer_test Sources/TracerTest_DFS.cxx
                               Headers/TracerTest.hxx
)
target_link_libraries(dfs_tracer_test PRIVATE graph_static)
add_test(NAME dfs_tracer COMMAND $<TARGET_FILE:dfs_tracer_test>)

add_executable(bfs_tracer_test Sources/TracerTest_BFS.cxx
                               Headers/TracerTest.hxx
)
target_link_libraries(bfs_tracer_test PRIVATE graph_static)
add_test(NAME bfs_tracer COMMAND $<TARGET_FILE:bfs_tracer_test>)


