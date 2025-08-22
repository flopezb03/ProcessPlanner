#include "planner.h"

#include <chrono>
#include <iostream>

void Planner::print(const time_point<steady_clock>& end, const std::string& name) const{
    auto duration = duration_cast<seconds>(end - start_time_).count();
    std::cout << duration << " s  - " << name << std::endl;
}