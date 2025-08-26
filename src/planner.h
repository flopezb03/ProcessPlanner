#ifndef PLANNER_H
#define PLANNER_H

#include <chrono>
#include <mutex>

#include "process.h"


class Planner {
    protected:
    std::mutex q_mutex_{};
    std::chrono::time_point<std::chrono::steady_clock> start_time_{};
    void print(const std::chrono::time_point<std::chrono::steady_clock>& end, const std::string& name) const;

    public:
    virtual ~Planner() = default;

    virtual void execute_processes() = 0;
    virtual void insert_process(const Process& p) = 0;
};



#endif //PLANNER_H
