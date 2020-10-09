cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-group)

find_package(MPI REQUIRED)

add_executable(fpmas-agent-group
	main.cpp)

target_link_libraries(fpmas-agent-group PUBLIC fpmas MPI::MPI_CXX zoltan)
