#ifndef PROCESS_H
#define PROCESS_H
#include <string>

typedef struct Process {
    std::string name_;
    int duration_;
    
    bool operator<(const Process& p) const {
        return p.duration_ < duration_;
    }
}Process;

#endif
