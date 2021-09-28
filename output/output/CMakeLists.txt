cmake_minimum_required(VERSION 3.10)

project(fpmas-output)

find_package(fpmas 1.2 REQUIRED)

add_executable(fpmas-output
	main.cpp
	)
target_link_libraries(fpmas-output PUBLIC fpmas::fpmas)
