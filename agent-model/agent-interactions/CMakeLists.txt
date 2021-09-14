cmake_minimum_required(VERSION 3.10)

project(fpmas-agent-interactions)

find_package(fpmas 1.1 REQUIRED)

if(NOT SYNC_MODE)
	message(FATAL_ERROR
"Undefined SYNC_MODE.
Please use the -DSYNC_MODE=[GhostMode/HardSyncMode] cmake option.")
endif()

add_executable(${PROJECT_NAME}
	${CMAKE_CURRENT_BINARY_DIR}/main.cpp
	src/agents.cpp)
include_directories(include)

target_compile_definitions(${PROJECT_NAME} PUBLIC SYNC_MODE=${SYNC_MODE})

target_link_libraries(${PROJECT_NAME} fpmas::fpmas)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
