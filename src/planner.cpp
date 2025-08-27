#include "planner.h"

#include <chrono>
#include <iostream>

using std::cout;
using std::endl;
using namespace std::chrono;

void Planner::print_exec_start(const time_point<steady_clock>& end, const std::string& name) const{
    long duration = duration_cast<milliseconds>(end - start_time_).count();
    cout << duration << " s  - " << name << endl;
}