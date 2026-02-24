#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <functional>
#include "Process.hpp"

class Kernel {
private:
    int next_pid = 1;
    int global_time = 0;
    int context_switches = 0;
    std::vector<std::shared_ptr<Process>> processes;
    std::queue<std::shared_ptr<Process>> ready_queue;

public:
    int create_process(int exec_time, std::function<void(int)> task);
    void run();
};