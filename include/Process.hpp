#pragma once
#include <functional>

enum class State {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
};

class Process {
public:
    int pid;
    State state;
    int remaining_time;

    int arrival_time = 0;
    int start_time = -1;
    int completion_time = -1;
    int waiting_time = 0;
    int turnaround_time = 0;

    std::function<void(int)> task;

    Process(int id, int exec_time, std::function<void(int)> t);
};