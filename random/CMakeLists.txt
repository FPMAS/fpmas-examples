cmake_minimum_required(VERSION 3.10)

project(fpmas-random)

find_package(fpmas 1.2 REQUIRED)

add_executable(fpmas-random-sequential
	sequential.cpp
	)
target_link_libraries(fpmas-random-sequential PUBLIC fpmas::fpmas)

add_executable(fpmas-random-distributed
	distributed.cpp
	)
target_link_libraries(fpmas-random-distributed PUBLIC fpmas::fpmas)

add_executable(fpmas-random-distribution
	distribution.cpp
	)
target_link_libraries(fpmas-random-distribution PUBLIC fpmas::fpmas)
