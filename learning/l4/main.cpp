#include <iostream>
#include "timer.h"

int main() {
    sp::timer t;
    t.reset();
    std::cout << "Hello, World!" << std::endl;
    std::cout<<t.get();

    return 0;
}