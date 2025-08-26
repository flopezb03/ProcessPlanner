#include <thread>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>

#include "process.h"
#include "planner.h"
#include "fcfs_planner.h"
#include "sjf_coop_planner.h"
#include "sjf_apr_planner.h"

using namespace std;

bool read_input(unique_ptr<Planner>& planner, std::queue<std::pair<Process,int>>& q) {
    ifstream processes_file;
    string line;

    // File opening
    try {
        processes_file.open("../src/processes_input.txt");
        if (!processes_file.is_open())
            throw runtime_error("Could not open processes_input.txt");
    }catch (exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    // First line => type of Process Planner to use
    getline(processes_file, line);
    if (line == "fcfs")
        planner = make_unique<FcfsPlanner>();
    else if (line == "sjf_coop")
        planner = make_unique<SjfCoopPlanner>();
    else if (line == "sjf_apr")
        planner = make_unique<SjfAprPlanner>();
    else {
        cerr << "Unknown planner type: " << line << endl;
        return false;
    }

    // Read processes times and start times
    int line_index = 1;
    while (getline(processes_file,line)) {
        istringstream iss(line);
        string p_name;
        int p_duration;
        int p_start;
        if (!(iss >> p_name >> p_duration >> p_start)) {
            cerr << "Invalid line: " << line_index << endl;
            return false;
        }
        q.push({Process(p_name,chrono::milliseconds(p_duration*1000)),p_start});
        line_index++;
    }
    return true;
}

void generator(Planner& planner, std::queue<std::pair<Process,int>>& q) {
    int time = 0;
    while (!q.empty()) {
        auto pair = q.front();
        q.pop();
        time = pair.second - time;
        std::this_thread::sleep_for(chrono::seconds(time));
        planner.insert_process(pair.first);
    }
}

int main() {
    unique_ptr<Planner> planner;
    std::queue<std::pair<Process,int>> processes_queue;

    //  Read input file
    read_input(planner,processes_queue);

    // Create threads
    thread t_gen(generator, ref(*planner), ref(processes_queue));
    thread t_planner(&Planner::execute_processes, ref(*planner));
    //planner->execute_processes();

    // Join threads
    t_gen.join();
    t_planner.join();


    return 0;
}
