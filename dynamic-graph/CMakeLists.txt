cmake_minimum_required(VERSION 3.10)

project(fpmas-dynamic-graph)


find_package(MPI REQUIRED)

set(SYNC_MODE "HardSyncMode" CACHE STRING "Graph Synchronization mode")
message("-- SYNC_MODE : ${SYNC_MODE}")

set(BUILD_NODE "fpmas-build-node")

add_executable(${BUILD_NODE}
	build_node.cpp dynamic_graph.cpp
	)
target_compile_definitions(${BUILD_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${BUILD_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)
