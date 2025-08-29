cmake_minimum_required(VERSION 3.31)
project(ProcessPlanner)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProcessPlanner src/main.cpp
        src/process.h
        src/planners/fcfs_planner.cpp
        src/planners/fcfs_planner.h
        src/planners/sjf_coop_planner.cpp
        src/planners/sjf_coop_planner.h
        src/planners/planner.h
        src/planners/planner.cpp
        src/planners/sjf_apr_planner.cpp
        src/planners/sjf_apr_planner.h
        src/planners/round_robin_planner.cpp
        src/planners/round_robin_planner.h)
