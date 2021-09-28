cmake_minimum_required(VERSION 3.10)

project(fpmas-dynamic-graph)


find_package(fpmas 1.2 REQUIRED)

set(SYNC_MODE "HardSyncMode" CACHE STRING "Graph Synchronization mode")
message("-- SYNC_MODE : ${SYNC_MODE}")


add_subdirectory(../../utils ${CMAKE_CURRENT_BINARY_DIR}/utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../../utils)

add_library(fpmas-dynamic-graph
	dynamic_graph.cpp)

set(LIBRARIES
	fpmas-example-utils fpmas-dynamic-graph fpmas::fpmas)

# LINK
set(LINK "fpmas-link")

add_executable(${LINK}
	link.cpp
	)
target_compile_definitions(${LINK} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${LINK} PUBLIC ${LIBRARIES})

# BUILD_NODE
set(BUILD_NODE "fpmas-build-node")

add_executable(${BUILD_NODE}
	build_node.cpp
	)
target_compile_definitions(${BUILD_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${BUILD_NODE} PUBLIC ${LIBRARIES})

# UNLINK
set(UNLINK "fpmas-unlink")

add_executable(${UNLINK}
	unlink.cpp
	)
target_compile_definitions(${UNLINK} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${UNLINK} PUBLIC ${LIBRARIES})

# REMOVE_NODE
set(REMOVE_NODE "fpmas-remove-node")

add_executable(${REMOVE_NODE}
	remove_node.cpp
	)
target_compile_definitions(${REMOVE_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${REMOVE_NODE} PUBLIC ${LIBRARIES})
