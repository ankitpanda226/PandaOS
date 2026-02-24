#include "Kernel.hpp"
#include <iostream>

int Kernel::create_process(int exec_time, std::function<void(int)> task) {
    auto proc = std::make_shared<Process>(next_pid++, exec_time, task);
    processes.push_back(proc);
    ready_queue.push(proc);
    return proc->pid;
}

void Kernel::run() {
    const int TIME_SLICE = 1;

    while (!ready_queue.empty()) {
        auto current = ready_queue.front();
        ready_queue.pop();

        if (current->state == State::TERMINATED)
            continue;

        current->state = State::RUNNING;

        std::cout << "[Kernel] Running Process " << current->pid << std::endl;

        current->task(TIME_SLICE);

        current->remaining_time -= TIME_SLICE;

        if (current->remaining_time <= 0) {
            current->state = State::TERMINATED;
            std::cout << "[Kernel] Process " << current->pid << " finished\n";
        } else {
            current->state = State::READY;
            ready_queue.push(current);
        }
    }
}