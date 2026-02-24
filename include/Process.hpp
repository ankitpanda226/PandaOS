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
    std::function<void()> task;

    Process(int id, std::function<void()> t);
};