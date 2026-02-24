#include "Process.hpp"

Process::Process(int id, std::function<void()> t)
    : pid(id), state(State::READY), task(t) {}