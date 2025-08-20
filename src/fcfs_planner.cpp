#include "fcfs_planner.h"

#include <chrono>
#include <iostream>
#include <thread>


void FcfsPlanner::print(const time_point<steady_clock>& end, const std::string& name) const{
    auto duration = duration_cast<seconds>(end - start_time_).count();
    std::cout << duration << " s  - " << name << std::endl;
}

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

        p.execute();
    }

    print(steady_clock::now(),"FIN");
}
