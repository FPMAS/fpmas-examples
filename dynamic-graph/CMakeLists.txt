cmake_minimum_required(VERSION 3.10)

project(fpmas-dynamic-graph)


find_package(MPI REQUIRED)

set(BUILD_NODE "fpmas-build-node")

add_executable(${BUILD_NODE}
	build_node.cpp dynamic_graph.cpp
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${BUILD_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)
