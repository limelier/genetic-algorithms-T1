//
// Created by tiacobescu on 20.10.2019.
//
#include "../config.h"
#include "methods.h"
#include "../util/bitset.h"

using Clock = std::chrono::high_resolution_clock;


result hillClimber(const std::function<double(std::vector<double>)>& function,
               double lower,
               double upper,
               double dimensions,
               bool steepestAscent) {

    const auto startTime = Clock::now();

    std::vector<bool> best;
    double bEval = BEST_INITIAL_VALUE;

    const auto CHUNK = bitsetSize(lower, upper, PRECISION);
    const auto BITS = CHUNK * dimensions;

    for (int attempt = 0; attempt < HILLCLIMBER_ATTEMPTS; attempt++) {
        bool local = false;

        auto candidate = generateBitset(BITS);
        auto cEval = function(bitsetToDoubles(candidate, CHUNK, lower, upper));

        while (!local) {
            auto neighbors = generateNeighbors(candidate);

            bool foundBetter = false;

            for (const auto& neighbor : neighbors) {
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
