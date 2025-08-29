#include <thread>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <string>

#include "process.h"
#include "planners/planner.h"
#include "planners/fcfs_planner.h"
#include "planners/sjf_coop_planner.h"
#include "planners/sjf_apr_planner.h"
#include "planners/round_robin_planner.h"

using namespace std;

int read_input(const string& ifile_path, unique_ptr<Planner>& planner, std::queue<std::pair<Process,int>>& q);
void generator(Planner& planner, std::queue<std::pair<Process,int>>& q);




int main(int argc, char** argv) {
    unique_ptr<Planner> planner;
    std::queue<std::pair<Process,int>> processes_queue;

    string ifile_path = "../resources/processes_input.txt";
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " wrong arguments" << endl;
        return 1;
    }
    if (argc == 2)
        ifile_path = argv[1];


    //  Read input file
    int read_out = read_input(ifile_path, planner,processes_queue);
    if (read_out != 0)
        return read_out;

    // Create threads
    thread t_gen(generator, ref(*planner), ref(processes_queue));
    thread t_planner(&Planner::execute_processes, ref(*planner));

    // Join threads
    t_gen.join();
    t_planner.join();


    return 0;
}



int read_input(const string& ifile_path, unique_ptr<Planner>& planner, std::queue<std::pair<Process,int>>& q) {
    ifstream processes_file;
    string line;

    // File opening
    processes_file.open(ifile_path);
    if (!processes_file.is_open()) {
        cerr << "Could not open processes_input.txt" << endl;
        return 2;
    }

    // First line => type of Process Planner to use
    getline(processes_file, line);
    if (line == "fcfs")
        planner = make_unique<FcfsPlanner>();
    else if (line == "sjf_coop")
        planner = make_unique<SjfCoopPlanner>();
    else if (line == "sjf_apr")
        planner = make_unique<SjfAprPlanner>();
    else if (line.substr(0,2) == "rr")
        planner = make_unique<RoundRobinPlanner>(1000*stoi(line.substr(3)));
    else {
        cerr << "Unknown planner type: " << line << endl;
        return 3;
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
    return 0;
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