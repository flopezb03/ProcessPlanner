#ifndef PROCESS_H
#define PROCESS_H
#include <string>

typedef struct Process {
    std::string name_;
    int duration_;
    void execute() const;
}Process;

#endif
