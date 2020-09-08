cmake_minimum_required(VERSION 3.10)

project(fpmas-example-utils)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME}
	utils.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC fpmas)


