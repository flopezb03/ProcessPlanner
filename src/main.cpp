#include <thread>
#include <fstream>
#include <regex>

#include "fcfs_planner.h"
#include "process.h"

using namespace std;

void generator(const std::vector<std::pair<Process,int>>& vec, FcfsPlanner& planner) {
    int time = 0;
    for (auto pair : vec) {
        time = pair.second - time;
        std::this_thread::sleep_for(seconds{time});
        planner.insert_process(pair.first);
    }
}

int main() {

    std::vector<std::pair<Process,int>> vec;
    vec.push_back({Process("P1",5),0});
    vec.push_back({Process("P2",5),3});
    vec.push_back({Process("P3",5),8});


    FcfsPlanner planner;

    std::thread gen(generator, std::cref(vec), std::ref(planner));
    std::thread t(&FcfsPlanner::execute_processes, &planner);

    gen.join();
    t.join();

    return 0;
}
