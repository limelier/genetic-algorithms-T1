//
// Created by tiacobescu on 20.10.2019.
//
#include <cmath>
#include "../config.h"
#include "methods.h"
#include "../util/bitset.h"
#include "../util/random.h"

using Clock = std::chrono::high_resolution_clock;

result hillClimber(const std::function<double(std::vector<double>)> &function,
                   double lower,
                   double upper,
                   double dimensions,
                   bool steepestAscent) {

    const auto startTime = Clock::now();

    std::vector<bool> best;
    double bEval = HILLCLIMBER_BEST_INIT_VALUE;

    const auto CHUNK = bitsetSize(lower, upper, PRECISION);
    const auto BITS = CHUNK * dimensions;

    for (int attempt = 0; attempt < HILLCLIMBER_ATTEMPTS; attempt++) {
        bool local = false;

        auto candidate = generateBitset(BITS);
        auto cEval = function(bitsetToDoubles(candidate, CHUNK, lower, upper));

        while (!local) {
            auto neighbors = generateNeighbors(candidate);

            bool foundBetter = false;

            for (const auto &neighbor : neighbors) {
                auto nEval = function(bitsetToDoubles(neighbor, CHUNK, lower, upper));

                if (nEval < cEval) {
                    candidate = neighbor;
                    cEval = nEval;
                    foundBetter = true;
                    if (!steepestAscent) break;
                }
            }

            if (!foundBetter) {
                local = true;
            }
        }

        if (cEval < bEval) {
            bEval = cEval;
            best = candidate;
        }
    }

    const auto endTime = Clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    return {bEval, bitsetToDoubles(best, CHUNK, lower, upper), duration};
}
result simulatedAnnealing(const std::function<double(std::vector<double>)> &function,
                          double lower,
                          double upper,
                          double dimensions) {
    const auto startTime = Clock::now();

    double temperature = ANNEALING_INITIAL_TEMPERATURE;

    const auto CHUNK = bitsetSize(lower, upper, PRECISION);
    const auto BITS = CHUNK * dimensions;

    auto candidate = generateBitset(BITS);
    auto cEval = function(bitsetToDoubles(candidate, CHUNK, lower, upper));

    for (int stage = 0; stage < ANNEALING_STAGES; stage++) {
        int consecutiveFailures = 0;
        while (consecutiveFailures < ANNEALING_CONSECUTIVE_FAILURE_MULT * dimensions) {
            auto neighbor = randomNeighbor(candidate);
            auto nEval = function(bitsetToDoubles(neighbor, CHUNK, lower, upper));

            if (nEval < cEval) {
                candidate = neighbor;
                cEval = nEval;
                    consecutiveFailures = 0;
            } else {
                double base = -(fabs(cEval - nEval) / temperature);
                if (randomSubunitary() < exp(base)) {
                    candidate = neighbor;
                    cEval = nEval;
                    consecutiveFailures = 0;
                } else {
                    consecutiveFailures++;
                }
            }
        }
        temperature *= double(stage + 1) / double(stage + 2);
    }

    const auto endTime = Clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    return {cEval, bitsetToDoubles(candidate, CHUNK, lower, upper), duration};
}
