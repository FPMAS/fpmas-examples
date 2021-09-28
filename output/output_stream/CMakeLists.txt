cmake_minimum_required(VERSION 3.10)

project(fpmas-output-watcher)

find_package(fpmas 1.1 REQUIRED)

add_executable(fpmas-output-cout
	cout.cpp
	)
target_link_libraries(fpmas-output-cout PUBLIC fpmas::fpmas)

add_executable(fpmas-output-string
	string_output.cpp
	)
target_link_libraries(fpmas-output-string PUBLIC fpmas::fpmas)

add_executable(fpmas-output-file
	file_output.cpp
	)
target_link_libraries(fpmas-output-file PUBLIC fpmas::fpmas)

add_executable(fpmas-output-dynamic-file
	dynamic_file_output.cpp
	)
target_link_libraries(fpmas-output-dynamic-file PUBLIC fpmas::fpmas)
