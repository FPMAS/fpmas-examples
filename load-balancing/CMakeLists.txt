cmake_minimum_required(VERSION 3.10)

project(fpmas-load-balancing)

find_package(fpmas 1.2 REQUIRED)

add_executable(fpmas-zoltan-graph zoltan-graph.cpp)
target_link_libraries(fpmas-zoltan-graph PUBLIC fpmas::fpmas)

add_executable(fpmas-zoltan-spatial-graph zoltan-spatial-graph.cpp)
target_link_libraries(fpmas-zoltan-spatial-graph PUBLIC fpmas::fpmas)

add_executable(fpmas-zoltan-grid zoltan-grid.cpp)
target_link_libraries(fpmas-zoltan-grid PUBLIC fpmas::fpmas)

add_executable(fpmas-zoltan-cell-spatial-graph zoltan-cell-spatial-graph.cpp)
target_link_libraries(fpmas-zoltan-cell-spatial-graph PUBLIC fpmas::fpmas)

add_executable(fpmas-zoltan-cell-grid zoltan-cell-grid.cpp)
target_link_libraries(fpmas-zoltan-cell-grid PUBLIC fpmas::fpmas)

add_executable(fpmas-grid-load-balancing grid-load-balancing.cpp)
target_link_libraries(fpmas-grid-load-balancing PUBLIC fpmas::fpmas)
