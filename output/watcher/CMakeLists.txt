cmake_minimum_required(VERSION 3.10)

project(fpmas-output-watcher)

find_package(fpmas 1.1 REQUIRED)

add_executable(fpmas-output-watcher
	main.cpp
	)
target_link_libraries(fpmas-output-watcher PUBLIC fpmas::fpmas)
