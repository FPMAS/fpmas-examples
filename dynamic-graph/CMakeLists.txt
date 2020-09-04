cmake_minimum_required(VERSION 3.10)

project(fpmas-dynamic-graph)


find_package(MPI REQUIRED)

set(SYNC_MODE "HardSyncMode" CACHE STRING "Graph Synchronization mode")
message("-- SYNC_MODE : ${SYNC_MODE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# LINK
set(LINK "fpmas-link")

add_executable(${LINK}
	link.cpp dynamic_graph.cpp
	)
target_compile_definitions(${LINK} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${LINK} PUBLIC fpmas MPI::MPI_CXX zoltan)

# BUILD_NODE
set(BUILD_NODE "fpmas-build-node")

add_executable(${BUILD_NODE}
	build_node.cpp dynamic_graph.cpp
	)
target_compile_definitions(${BUILD_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${BUILD_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)

# UNLINK
set(UNLINK "fpmas-unlink")

add_executable(${UNLINK}
	unlink.cpp dynamic_graph.cpp
	)
target_compile_definitions(${UNLINK} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${UNLINK} PUBLIC fpmas MPI::MPI_CXX zoltan)

# REMOVE_NODE
set(REMOVE_NODE "fpmas-remove-node")

add_executable(${REMOVE_NODE}
	remove_node.cpp dynamic_graph.cpp
	)
target_compile_definitions(${REMOVE_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${REMOVE_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)


