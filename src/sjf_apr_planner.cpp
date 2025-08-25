//
// Created by ferloz97 on 25/08/25.
//

#include "sjf_apr_planner.h"

#include <iostream>
#include <thread>


void SjfAprPlanner::execute_processes() {
    using namespace std::chrono;

    std::this_thread::sleep_for(milliseconds{100});

    start_time_ = steady_clock::now();

    while (!q_.empty()) {
        q_mutex_.lock();
        Process p = q_.top();
        q_.pop();
        q_mutex_.unlock();

        print(steady_clock::now(),p.name_);

        std::unique_lock lck{cv_mutex_};
        time_point<steady_clock> prev = steady_clock::now();
        if (cv_.wait_for(lck,seconds(p.duration_)) != std::cv_status::timeout) {
            int p_exec_time = duration_cast<seconds>(steady_clock::now() - prev).count();
            p.duration_ -= p_exec_time;
            q_mutex_.lock();
            q_.push(p);
            q_mutex_.unlock();
        }
    }

    print(steady_clock::now(),"FIN");
}

void SjfAprPlanner::insert_process(const Process& p) {
    q_mutex_.lock();
    q_.push(p);
    std::scoped_lock lck{cv_mutex_};
    cv_.notify_one();
    q_mutex_.unlock();
}