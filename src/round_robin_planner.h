#ifndef RR_PLANNER_H
#define RR_PLANNER_H

#include <condition_variable>

#include "fcfs_planner.h"


class RoundRobinPlanner : public FcfsPlanner {
    protected:
    std::chrono::milliseconds quantum_;
    std::condition_variable p_duration_cv;
    std::condition_variable q_duration_cv_;
    std::mutex quantum_mutex_;
    bool q_clock_active_;

    public:
    explicit RoundRobinPlanner(int quantum): quantum_{quantum}, q_clock_active_ {true} {};

    void execute_processes() override;
    void quantum_clock();
};



#endif //RR_PLANNER_H
