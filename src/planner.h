#ifndef PLANNER_H
#define PLANNER_H

#include <chrono>
#include <mutex>

#include "process.h"

using namespace std::chrono;



class Planner {
    protected:
    std::mutex q_mutex_{};
    time_point<steady_clock> start_time_{};
    void print(const time_point<steady_clock>& end, const std::string& name) const;

    public:
    virtual ~Planner() = default;

    virtual void execute_processes() = 0;
    virtual void insert_process(const Process& p) = 0;
};



#endif //PLANNER_H
