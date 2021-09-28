cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-serialization)

find_package(fpmas 1.2 REQUIRED)

add_executable(fpmas-agent-serialization
	src/main.cpp
	src/agents.cpp
	)

include_directories(fpmas-agent-serialization include)
target_link_libraries(fpmas-agent-serialization PUBLIC fpmas::fpmas)
