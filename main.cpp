#include <iostream>
#include "src/methods.h"
#include "util/functions.h"

int main() {
    auto res = simulatedAnnealing(rastrigin, -5.12, 5.12, 20);
    std::cout << res.fx << ' ' << res.time;
}