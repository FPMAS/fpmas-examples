cmake_minimum_required(VERSION 3.10)

project(fpmas-get-started)

find_package(fpmas 1.1 REQUIRED)

add_executable(fpmas-get-started
	src/main.cpp
	src/agents.cpp
	)

include_directories(fpmas-get-started include)
target_link_libraries(fpmas-get-started PUBLIC fpmas::fpmas)
