#include "Kernel.hpp"
#include <iostream>

int main() {
    Kernel os;

    os.create_process(3, [](int slice) {
        std::cout << "Process 1 executing for " << slice << " unit\n";
    });

    os.create_process(2, [](int slice) {
        std::cout << "Process 2 executing for " << slice << " unit\n";
    });

    os.run();

    return 0;
}