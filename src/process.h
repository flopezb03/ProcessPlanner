#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <chrono>


typedef struct Process {
    std::string name_;
    std::chrono::milliseconds duration_;

    bool operator<(const Process& p) const {
        return p.duration_ < duration_;
    }
}Process;

#endif
