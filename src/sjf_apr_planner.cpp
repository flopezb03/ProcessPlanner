#include "sjf_apr_planner.h"

#include <thread>

using namespace std::chrono;

void SjfAprPlanner::execute_processes() {
    //  Init time
    std::this_thread::sleep_for(milliseconds{1}); // Give time to the generator thread to push process in the queue
    start_time_ = steady_clock::now();

    while (!q_.empty()) {
        //  Pop first process
        q_mutex_.lock();
        Process p = q_.top();
        q_.pop();
        q_mutex_.unlock();

        print_exec_start(steady_clock::now(),p.name_);

        std::unique_lock lck{cv_mutex_};
        time_point<steady_clock> prev = steady_clock::now();
        if (cv_.wait_for(lck,p.duration_) != std::cv_status::timeout) { // Executing process
            //  If a new process was pushed in queue while executing process
            milliseconds p_exec_time = duration_cast<milliseconds>(steady_clock::now() - prev); //  Time of execution
            p.duration_ -= p_exec_time;     // Updated execution time
            q_mutex_.lock();
            q_.push(p);                     // Back to the queue
            q_mutex_.unlock();
        }
    }

    print_exec_start(steady_clock::now(),"END");
}

void SjfAprPlanner::insert_process(const Process& p) {
    q_mutex_.lock();
    q_.push(p);
    std::scoped_lock lck{cv_mutex_};
    cv_.notify_one();
    q_mutex_.unlock();
}