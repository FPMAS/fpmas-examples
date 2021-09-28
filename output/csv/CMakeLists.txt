cmake_minimum_required(VERSION 3.10)

project(fpmas-output-csv)

find_package(fpmas 1.2 REQUIRED)

add_library(fpmas-output-csv
	src/agent.cpp
	)
target_include_directories(fpmas-output-csv PUBLIC include)
target_link_libraries(fpmas-output-csv PUBLIC fpmas::fpmas)

add_executable(fpmas-output-basic-csv
	basic_csv.cpp
	)
target_include_directories(fpmas-output-basic-csv PUBLIC include)
target_link_libraries(fpmas-output-basic-csv PUBLIC fpmas-output-csv)

add_executable(fpmas-output-agent-csv
	agent_csv.cpp
	)
target_include_directories(fpmas-output-agent-csv PUBLIC include)
target_link_libraries(fpmas-output-agent-csv PUBLIC fpmas-output-csv)

add_executable(fpmas-output-distributed-agent-csv
	src/agent.cpp
	distributed_agent_csv.cpp
	)
target_include_directories(fpmas-output-distributed-agent-csv PUBLIC include)
target_link_libraries(fpmas-output-distributed-agent-csv PUBLIC fpmas-output-csv)
