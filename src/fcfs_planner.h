#ifndef FCFS_PLANNER_H
#define FCFS_PLANNER_H

#include <queue>

#include "planner.h"
#include "process.h"

class FcfsPlanner : public Planner {
    protected:
    std::queue<Process> q_{};

    public:
    void execute_processes() override;
    void insert_process(const Process& p) override;
};



#endif //FCFS_PLANNER_H
