#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <functional>

#include "Process.hpp"

class Kernel {
private:
    int next_pid = 1;
    std::vector<std::shared_ptr<Process>> processes;
    std::queue<std::shared_ptr<Process>> ready_queue;

public:
    int create_process(std::function<void()> task);
    void run();
};