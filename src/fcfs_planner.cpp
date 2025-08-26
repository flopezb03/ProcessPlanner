#include "fcfs_planner.h"

#include <chrono>
#include <thread>

void FcfsPlanner::insert_process(const Process& p) {
    q_mutex_.lock();
    q_.push(p);
    q_mutex_.unlock();
}

void FcfsPlanner::execute_processes() {
    using namespace std::chrono;

    std::this_thread::sleep_for(milliseconds{100});

    start_time_ = steady_clock::now();

    while (!q_.empty()) {
        q_mutex_.lock();
        Process p = q_.front();
        q_.pop();
        q_mutex_.unlock();

        print(steady_clock::now(),p.name_);

        std::this_thread::sleep_for(std::chrono::seconds{p.duration_});
    }

    print(steady_clock::now(),"FIN");
}
