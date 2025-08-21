#include <thread>
#include <fstream>
#include <iostream>
#include <regex>

#include "fcfs_planner.h"
#include "process.h"

using namespace std;

void generator(std::queue<std::pair<Process,int>>& q, FcfsPlanner& planner) {
    int time = 0;
    while (!q.empty()) {
        auto pair = q.front();
        q.pop();
        time = pair.second - time;
        std::this_thread::sleep_for(seconds{time});
        planner.insert_process(pair.first);
    }
}

int main() {

    //  Read input file

    std::queue<std::pair<Process,int>> processes_queue;
    ifstream processes_file;
    try {
        processes_file.open("../src/processes_input.txt");
        if (!processes_file.is_open())
            throw runtime_error("Could not open processes_input.txt");
    }catch (exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    string line;
    int line_index = 0;
    while (getline(processes_file,line)) {
        istringstream iss(line);
        string p_name;
        int p_duration;
        int p_start;
        if (!(iss >> p_name >> p_duration >> p_start)) {
            cerr << "Invalid line: " << line_index << endl;
        }
        processes_queue.push({Process(p_name,p_duration),p_start});
        line_index++;
    }

    // Create threads

    FcfsPlanner planner;

    std::thread t_gen(generator, std::ref(processes_queue), std::ref(planner));
    std::thread t_planner(&FcfsPlanner::execute_processes, &planner);

    // Join threads

    t_gen.join();
    t_planner.join();

    return 0;
}
