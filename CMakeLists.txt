cmake_minimum_required(VERSION 3.3)
project(QueueSystemSimulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp src/dist_functions.cpp src/frecuencies.cpp src/prob.cpp
        src/prob_tests.cpp src/readers.cpp src/writers.cpp)
add_executable(QueueSystemSimulator ${SOURCE_FILES})