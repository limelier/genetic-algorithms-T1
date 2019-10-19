//
// Created by tiacobescu on 15.10.2019.
//

#include <cmath>
#include <functional>
#include <random>

bool randomBool() {
    static std::random_device random_device;
    static thread_local auto generator = std::mt19937_64(random_device());
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1), generator);

    return gen();
}

#include "bitsetFuncs.h"
std::size_t bitsetSize(double lower, double upper, int precision) {
    // precision: interpreted as (upper - lower) * 10^-precision
    double intervalLength = upper - lower;
    int values = int(intervalLength * pow(10, precision));
    size_t bits = ceil(log2(values));
    return bits;
}
std::vector<bool> generateBitset(size_t size) {
    std::vector<bool> bitset;
    for (size_t i = 0; i < size; i++) {
        bitset.push_back(bool(randomBool()));
    }
    return bitset;
}
std::vector<std::vector<bool>> neighbors(std::vector<bool> &bitset) {
    const size_t size = bitset.size();
    std::vector<std::vector<bool>> neighbors;
    typeof(bitset) neighbor;
    for (size_t i = 0; i < size; i++) {
        neighbor = bitset;
        neighbor[i] = !neighbor[i];
        neighbors.push_back(neighbor);
    }
    return neighbors;
}
