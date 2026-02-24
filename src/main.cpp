#include "Kernel.hpp"
#include <iostream>

int main() {
    Kernel os;

    os.create_process([]() {
        std::cout << "Process 1 executing\n";
    });

    os.create_process([]() {
        std::cout << "Process 2 executing\n";
    });

    os.run();

    return 0;
}