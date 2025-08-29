#include "sjf_coop_planner.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

void SjfCoopPlanner::execute_processes() {
    //  Init time
    std::this_thread::sleep_for(nanoseconds{1}); // Give time to the generator thread to push process in the queue
    start_time_ = steady_clock::now();

    while (!q_.empty()) {
        //  Pop first process
        q_mutex_.lock();
        Process p = q_.top();
        q_.pop();
        q_mutex_.unlock();

        //  Exec
        print_exec_start(steady_clock::now(),p.name_);
        std::this_thread::sleep_for(p.duration_);
    }

    print_exec_start(steady_clock::now(),"END");
}

void SjfCoopPlanner::insert_process(const Process& p) {
    q_mutex_.lock();
    q_.push(p);
    q_mutex_.unlock();
}
