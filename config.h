#ifndef T1_PROJECT__CONFIG_H_
#define T1_PROJECT__CONFIG_H_

#include <cstddef>
const int ALGORITHM_RUNS = 30;

const double ANNEALING_STOPPING_TRESHHOLD = 1;
const double ANNEALING_INITIAL_TEMPERATURE = 1000; // keep this high to illustrate a point on michalewicz
const int ANNEALING_CONSEC_FAILURE_LIMIT = 2;
const size_t ANNEALING_MAX_TIME_MS = 300000; // 5 min

const int HILLCLIMBER_ATTEMPTS = 1000;
const double HILLCLIMBER_BEST_INIT_VALUE = 100000000.0;
const size_t HILLCLIMBER_MS_PER_ATTEMPT = 300000 / HILLCLIMBER_ATTEMPTS; // usually, 0.3s per attempt

const int PRECISION = 10;

#endif //T1_PROJECT__CONFIG_H_
