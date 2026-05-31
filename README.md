# PandaOS

PandaOS is a modular, event-driven scheduling simulation engine written in C++17. It models core operating system scheduling behavior through a clean architecture built around process lifecycle state, pluggable scheduler strategies, tick-based execution, I/O blocking, metrics collection, benchmarking, and timeline visualization.

## Features

### Scheduling

- Strategy-based `Scheduler` interface
- First-Come, First-Served (FCFS) scheduler
- Round Robin scheduler
- Scheduler-defined dispatch quantum
- Kernel execution loop remains independent of policy-specific scheduling logic

### Simulation Engine

- Clock-driven event loop with one-tick execution semantics
- Explicit process lifecycle modeling:

  ```text
  READY -> RUNNING -> BLOCKED -> READY -> TERMINATED
  ```

- I/O blocking simulation using a blocked queue
- Blocked-to-ready transitions after simulated I/O completion
- Context switch tracking
- Global simulation time

### Metrics and Observability

- Structured scheduler metrics
- Average turnaround time
- Average waiting time
- Total context switches
- Benchmark mode comparing FCFS and Round Robin on identical workloads
- Timeline recording for each clock tick
- ASCII timeline visualization
- JSON export for metrics, benchmark results, and timelines

### Project Structure

- Modular CMake-based multi-file C++ project
- Separate components for:
  - Kernel execution
  - Scheduler policy
  - Process control block state
  - Metrics
  - Timeline recording
  - Presentation and CLI behavior

## Architecture

```text
                      +----------------+
                      |    main.cpp    |
                      | CLI / Output   |
                      +--------+-------+
                               |
                               v
                      +----------------+
                      |     Kernel     |
                      | Event Loop     |
                      | Clock / State  |
                      +---+--------+---+
                          |        |
              records     |        | delegates
                          v        v
              +----------------+  +------------------+
              | Timeline       |  | Scheduler        |
              | Recorder       |  | Interface        |
              +----------------+  +--------+---------+
                                            |
                              +-------------+-------------+
                              |                           |
                              v                           v
                     +----------------+          +--------------------+
                     | FCFS Scheduler |          | RoundRobinScheduler|
                     +----------------+          +--------------------+

                      +----------------+
                      |    Process     |
                      | PCB / State    |
                      +----------------+
```

The kernel owns simulation time, process state transitions, blocked queue management, and metrics collection. Scheduling policy is delegated through the `Scheduler` interface. Timeline export and presentation are kept outside the kernel.

## Build Instructions

### Requirements

- C++17-compatible compiler
- CMake 3.10 or newer

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Run

```bash
./build/pandaos
```

## CLI Usage

Run with the default scheduling policy:

```bash
./build/pandaos
```

Run with FCFS:

```bash
./build/pandaos --policy=fcfs
```

Run with Round Robin:

```bash
./build/pandaos --policy=rr
```

Run benchmark mode:

```bash
./build/pandaos --benchmark
```

Benchmark mode executes the same workload under both scheduling policies and writes results to:

```text
benchmark.json
```

Normal scheduler runs write timeline data to:

```text
timeline.json
```

## Sample Output

### Benchmark

```text
===== Scheduler Benchmark =====
Policy | Context Switches | Avg Turnaround | Avg Waiting
---------------------------------------------------------
FCFS | 3 | 6 | 2.66667
ROUND_ROBIN | 10 | 7.33333 | 4

Benchmark results written to benchmark.json
```

### Timeline

```text
===== Timeline =====
Time:  0  1  2  3  4  5  6  7  8  9
P1:    #        #        #
P2:       #        #
P3:          #        #     #  #  #

Timeline written to timeline.json
```

### Timeline JSON

```json
{
    "timeline": [
        {
            "pid": 1,
            "time": 0
        },
        {
            "pid": 2,
            "time": 1
        },
        {
            "pid": 3,
            "time": 2
        }
    ]
}
```

## Design Philosophy

PandaOS is designed around separation of concerns. The kernel advances simulated time and owns process lifecycle transitions, while scheduling decisions are isolated behind the `Scheduler` interface. Concrete schedulers define their own queue behavior and dispatch quantum, which keeps the kernel free of policy-specific branching.

Metrics and timeline output are treated as observability concerns rather than scheduling concerns. This keeps the simulation core small, testable, and extensible while still making behavior easy to inspect through JSON exports and ASCII timelines.

## Future Extensions

- Priority scheduling
- Shortest Job First and Shortest Remaining Time First
- Multi-level feedback queue scheduling
- Configurable process workloads from JSON
- Explicit process arrival times
- Multiple I/O events per process
- CPU utilization and throughput metrics
- Unit tests for scheduler behavior and kernel lifecycle transitions
- Trace replay and deterministic workload fixtures
- Web-based timeline visualization

## Technologies

- C++17
- CMake
- nlohmann/json
- Object-oriented design
- Strategy pattern
- Event-driven simulation
- Scheduling algorithms
- Process lifecycle modeling
