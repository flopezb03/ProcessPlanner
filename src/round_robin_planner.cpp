#include "round_robin_planner.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

void RoundRobinPlanner::execute_processes() {
    //  Init time
    std::this_thread::sleep_for(nanoseconds{1}); // Give time to the generator thread to push process in the queue
    start_time_ = steady_clock::now();
    std::thread q_clock(&RoundRobinPlanner::quantum_clock,this);

    while (!q_.empty()) {
        //  Pop first process
        q_mutex_.lock();
        Process p = q_.front();
        q_.pop();
        q_mutex_.unlock();

        print_exec_start(steady_clock::now(),p.name_);

        std::unique_lock lck{process_duration_cv_mutex_};
        time_point<steady_clock> prev = steady_clock::now();
        if (p_duration_cv.wait_for(lck,p.duration_) != std::cv_status::timeout) { // Executing process
            //  If a new process was pushed in queue while executing process
            milliseconds p_exec_time = duration_cast<milliseconds>(steady_clock::now() - prev); //  Time of execution
            p.duration_ -= p_exec_time;     // Updated execution time
            q_mutex_.lock();
            q_.push(p);                     // Back to the queue
            q_mutex_.unlock();
        }else {
            //  Quantum restart
            std::scoped_lock q_lock{quantum_duration_cv_mutex_};
            q_duration_cv_.notify_one();
        }
    }
    q_clock_active_ = false;
    print_exec_start(steady_clock::now(),"END");
    q_clock.join();
}

void RoundRobinPlanner::quantum_clock() {
    //  Clock of `RoundRobinPlanner::quantum_` millis, can be reset if the process longs less
    while (q_clock_active_) {
        std::unique_lock q_lock{quantum_duration_cv_mutex_};
        if (q_duration_cv_.wait_for(q_lock,quantum_) == std::cv_status::timeout) {
            //  Notify to stop the current process executing
            std::scoped_lock lck{process_duration_cv_mutex_};
            p_duration_cv.notify_one();
        }
    }
}