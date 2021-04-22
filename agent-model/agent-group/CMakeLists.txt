cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-group)

find_package(fpmas 1.1 REQUIRED)

add_executable(fpmas-agent-group
	agents.cpp
	main.cpp)

target_link_libraries(fpmas-agent-group PUBLIC fpmas::fpmas)
