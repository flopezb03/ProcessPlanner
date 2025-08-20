cmake_minimum_required(VERSION 3.31)
project(ProcessPlanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProcessPlanner src/main.cpp
        src/process.h
        src/fcfs_planner.cpp
        src/fcfs_planner.h
        src/process.cpp)
