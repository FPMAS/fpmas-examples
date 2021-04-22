cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-scheduling)

find_package(fpmas 1.1 REQUIRED)

add_executable(fpmas-agent-scheduling
	main.cpp)

target_link_libraries(fpmas-agent-scheduling PUBLIC fpmas::fpmas)
