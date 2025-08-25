//
// Created by ferloz97 on 25/08/25.
//

#ifndef SJF_APR_PLANNER_H
#define SJF_APR_PLANNER_H

#include <condition_variable>

#include "sjf_coop_planner.h"


class SjfAprPlanner : public SjfCoopPlanner {
    protected:
    std::condition_variable cv_;
    std::mutex cv_mutex_;
    public:
    void execute_processes() override;
    void insert_process(const Process& p) override;
};



#endif //SJF_APR_PLANNER_H
