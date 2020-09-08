cmake_minimum_required(VERSION 3.10)

project(fpmas-dynamic-graph)


find_package(MPI REQUIRED)

set(SYNC_MODE "HardSyncMode" CACHE STRING "Graph Synchronization mode")
message("-- SYNC_MODE : ${SYNC_MODE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../utils)
add_subdirectory(../utils ${CMAKE_CURRENT_BINARY_DIR}/utils)

set(LIBRARIES fpmas-example-utils fpmas MPI::MPI_CXX zoltan)

# BASIC_DISTRIB
set(BASIC_DISTRIB "fpmas-basic-distribution")

add_executable(${BASIC_DISTRIB}
	basic_distribution.cpp
	)
target_compile_definitions(${BASIC_DISTRIB} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${BASIC_DISTRIB} PUBLIC ${LIBRARIES})

## BUILD_NODE
#set(BUILD_NODE "fpmas-build-node")

#add_executable(${BUILD_NODE}
	#build_node.cpp dynamic_graph.cpp
	#)
#target_compile_definitions(${BUILD_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

#target_link_libraries(${BUILD_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)

## UNLINK
#set(UNLINK "fpmas-unlink")

#add_executable(${UNLINK}
	#unlink.cpp dynamic_graph.cpp
	#)
#target_compile_definitions(${UNLINK} PUBLIC SYNC_MODE=${SYNC_MODE})

#target_link_libraries(${UNLINK} PUBLIC fpmas MPI::MPI_CXX zoltan)

## REMOVE_NODE
#set(REMOVE_NODE "fpmas-remove-node")

#add_executable(${REMOVE_NODE}
	#remove_node.cpp dynamic_graph.cpp
	#)
#target_compile_definitions(${REMOVE_NODE} PUBLIC SYNC_MODE=${SYNC_MODE})

#target_link_libraries(${REMOVE_NODE} PUBLIC fpmas MPI::MPI_CXX zoltan)


