#include "Process.hpp"

Process::Process(int id, int exec_time, std::function<void(int)> t)
    : pid(id),
      state(State::READY),
      remaining_time(exec_time),
      task(t) {}