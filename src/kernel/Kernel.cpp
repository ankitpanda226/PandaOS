#include "Kernel.hpp"
#include <iostream>

int Kernel::create_process(std::function<void()> task) {
    auto proc = std::make_shared<Process>(next_pid++, task);
    processes.push_back(proc);
    ready_queue.push(proc);
    return proc->pid;
}

void Kernel::run() {
    while (!ready_queue.empty()) {
        auto proc = ready_queue.front();
        ready_queue.pop();

        proc->state = State::RUNNING;
        std::cout << "[Kernel] Running Process " << proc->pid << std::endl;

        proc->task();

        proc->state = State::TERMINATED;
    }
}