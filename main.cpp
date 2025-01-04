#include <iostream>
#include <stdexcept>

int main() {
    throw std::runtime_error("This is a forced runtime error");

    return 0;
}