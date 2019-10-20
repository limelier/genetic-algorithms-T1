#include <iostream>
#include "src/methods.h"
#include "util/functions.h"

int main() {
    auto res = hillClimber(rastrigin, -5.12, 5.12, 30, true);
    std::cout << res.fx << ' ' << res.time << "ms";
}