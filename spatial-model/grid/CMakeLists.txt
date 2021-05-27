cmake_minimum_required(VERSION 3.14)

project(fpmas-grid)

find_package(fpmas 1.1 REQUIRED)

add_executable(${PROJECT_NAME}
	main.cpp
	src/agents.cpp)
include_directories(include)

target_link_libraries(${PROJECT_NAME} fpmas::fpmas)
