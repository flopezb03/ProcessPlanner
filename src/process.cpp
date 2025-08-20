#include "process.h"

#include <thread>

void Process::execute() const{
    std::this_thread::sleep_for(std::chrono::seconds{duration_});
}
