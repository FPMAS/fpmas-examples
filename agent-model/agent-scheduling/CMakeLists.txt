cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-scheduling)

find_package(fpmas 1.2 REQUIRED)

add_executable(fpmas-agent-scheduling
	agents.cpp
	main.cpp)

target_link_libraries(fpmas-agent-scheduling PUBLIC fpmas::fpmas)
