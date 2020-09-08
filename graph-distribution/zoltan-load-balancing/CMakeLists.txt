cmake_minimum_required(VERSION 3.10)

project(zoltan-load-balancing)


find_package(MPI REQUIRED)

set(SYNC_MODE "HardSyncMode" CACHE STRING "Graph Synchronization mode")
message("-- SYNC_MODE : ${SYNC_MODE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ../../utils)
add_subdirectory(../../utils ${CMAKE_CURRENT_BINARY_DIR}/utils)

add_executable(${PROJECT_NAME}
	main.cpp
	)

target_compile_definitions(${PROJECT_NAME} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${PROJECT_NAME} PUBLIC fpmas-example-utils fpmas MPI::MPI_CXX zoltan)
