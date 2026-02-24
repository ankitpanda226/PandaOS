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

        if (current->start_time == -1)
            current->start_time = global_time;

        current->state = State::RUNNING;

        std::cout << "[Time " << global_time << "] Running Process "
                  << current->pid << std::endl;

        current->task(TIME_SLICE);

        global_time += TIME_SLICE;
        current->remaining_time -= TIME_SLICE;
        context_switches++;

        if (current->remaining_time <= 0) {
            current->state = State::TERMINATED;
            current->completion_time = global_time;
            current->turnaround_time =
                current->completion_time - current->arrival_time;
            current->waiting_time =
                current->turnaround_time - (current->completion_time - current->start_time);

            std::cout << "[Kernel] Process "
                      << current->pid << " finished\n";
        } else {
            current->state = State::READY;
            ready_queue.push(current);
        }
    }

    // Print summary
    std::cout << "\n===== Scheduler Metrics =====\n";
    for (auto &p : processes) {
        std::cout << "Process " << p->pid
                  << " | Turnaround: " << p->turnaround_time
                  << " | Waiting: " << p->waiting_time
                  << std::endl;
    }

    std::cout << "Total Context Switches: "
              << context_switches << std::endl;
}