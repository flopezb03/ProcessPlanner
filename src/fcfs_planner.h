#ifndef FCFS_PLANNER_H
#define FCFS_PLANNER_H
#include <chrono>
#include <mutex>
#include <queue>

#include "process.h"

using namespace std::chrono;

class FcfsPlanner {
    std::queue<Process> q_{};
    std::mutex q_mutex_{};
    time_point<steady_clock> start_time_{};
    void print(const time_point<steady_clock>& end, const std::string& name) const;


    public:
    void execute_processes();
    void insert_process(const Process& p);

};



#endif //FCFS_PLANNER_H
