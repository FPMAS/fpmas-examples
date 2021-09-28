cmake_minimum_required(VERSION 3.10)

project(fpmas-output-json)

find_package(fpmas 1.2 REQUIRED)

add_library(fpmas-output-json
	src/agent.cpp
	)
target_include_directories(fpmas-output-json PUBLIC include)
target_link_libraries(fpmas-output-json PUBLIC fpmas::fpmas)

add_executable(fpmas-output-basic-json
	basic_json.cpp
	)
target_include_directories(fpmas-output-basic-json PUBLIC include)
target_link_libraries(fpmas-output-basic-json PUBLIC fpmas-output-json)

add_executable(fpmas-output-agent-json
	agent_json.cpp
	)
target_include_directories(fpmas-output-agent-json PUBLIC include)
target_link_libraries(fpmas-output-agent-json PUBLIC fpmas-output-json)

add_executable(fpmas-output-agent-view-json
	src/agent_view.cpp
	agent_view_json.cpp
	)
target_include_directories(fpmas-output-agent-view-json PUBLIC include)
target_link_libraries(fpmas-output-agent-view-json PUBLIC fpmas-output-json)
