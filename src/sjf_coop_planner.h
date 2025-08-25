#ifndef SJF_COOP_PLANNER_H
#define SJF_COOP_PLANNER_H

#include <mutex>
#include <queue>

#include "planner.h"
#include "process.h"

using namespace std::chrono;

class SjfCoopPlanner : public Planner {
    protected:
    std::priority_queue<Process> q_{};

    public:
    void execute_processes() override;
    void insert_process(const Process& p) override;
};



#endif //SJF_COOP_PLANNER_H
