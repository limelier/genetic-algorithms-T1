//
// Created by tiacobescu on 20.10.2019.
//

#ifndef T1_PROJECT_SRC_METHODS_H_
#define T1_PROJECT_SRC_METHODS_H_

#include <functional>
#include "../util/result.h"

result hillClimber(const std::function<double(std::vector<double>)>&, double lower, double upper, double dimensions, bool steepestAscent);

#endif //T1_PROJECT_SRC_METHODS_H_
