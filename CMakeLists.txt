cmake_minimum_required(VERSION 3.12)
project(FindEulerCycle)

set(CMAKE_CXX_STANDARD 14)

add_executable(FindEulerCycle main.cpp Graph.h Graph.cpp GraphTest.h OptimusGraph.h OptimusGraph.cpp Interface.cpp Interface.h)