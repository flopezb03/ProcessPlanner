#include "sjf_coop_planner.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

void SjfCoopPlanner::insert_process(const Process& p) {
    q_mutex_.lock();
    q_.push(p);
    q_mutex_.unlock();
}

void SjfCoopPlanner::execute_processes() {
    std::this_thread::sleep_for(milliseconds{100});

    start_time_ = steady_clock::now();

    while (!q_.empty()) {
        q_mutex_.lock();
        Process p = q_.top();
        q_.pop();
        q_mutex_.unlock();

        print(steady_clock::now(),p.name_);

        std::this_thread::sleep_for(p.duration_);
    }

    print(steady_clock::now(),"FIN");
}
