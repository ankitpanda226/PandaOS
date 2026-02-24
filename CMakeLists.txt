cmake_minimum_required(VERSION 3.10)
project(PandaOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(pandaos
    src/main.cpp
    src/kernel/Kernel.cpp
    src/process/Process.cpp
)

target_include_directories(pandaos PUBLIC include)