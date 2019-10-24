//
// Created by tiacobescu on 20.10.2019.
//

#ifndef T1_PROJECT_SRC_METHODS_H_
#define T1_PROJECT_SRC_METHODS_H_

#include <functional>
#include "../util/result.h"
#include "../util/functions.h"

result hillClimber(const testFunction &function,
                   double lower,
                   double upper,
                   int dimensions,
                   bool steepestAscent);
result simulatedAnnealing(const testFunction &function,
                          double lower,
                          double upper,
                          int dimensions);

auto hillClimberSA = [](const auto& function, auto lower, auto upper, auto dimensions) {
    return hillClimber(function, lower, upper, dimensions, true);
};
auto hillClimberFA = [](const auto& function, auto lower, auto upper, auto dimensions) {
    return hillClimber(function, lower, upper, dimensions, false);
};

typedef std::function<result(testFunction, double, double, int)> testMethod;

#endif //T1_PROJECT_SRC_METHODS_H_
