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
    std::function<void(int)> task;

    Process(int id, int exec_time, std::function<void(int)> t);
};