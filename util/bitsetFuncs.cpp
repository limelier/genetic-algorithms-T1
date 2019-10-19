//
// Created by tiacobescu on 15.10.2019.
//

#include <cmath>
#include <functional>
#include <random>

bool randomBool() {
    static std::random_device randomDevice;
    static thread_local auto generator = std::mt19937_64(randomDevice());
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
std::vector<std::vector<bool>> generateNeighbors(std::vector<bool> &bitset) {
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

double bitsetToDouble(const std::vector<bool>& bitset, size_t bits, double lower, double upper) {
    double result = lower;
    double bitValue = (upper - lower) / pow(2, bits);

    for (size_t i = 1; i <= bits; i++) {
        if (bitset[bits - i]) {
             result += bitValue;
        }
        bitValue *= 2;
    }

    return result;
}
std::vector<bool> mergeBitsets(const std::vector<std::vector<bool>>& bitsets) {
    std::vector<bool> result;
    const size_t chunks = bitsets.size();
    const size_t chunkSize = bitsets[0].size();
    const size_t size = chunks * chunkSize;

    result.reserve(size);
    for (auto bitset : bitsets) {
        result.insert(result.end(), bitset.begin(), bitset.end());
    }

    return result;
}
std::vector<std::vector<bool>> splitBitset(std::vector<bool> bitset, size_t chunkSize) {
    std::vector<std::vector<bool>> result;
    const size_t chunks = bitset.size() / chunkSize;

    for (size_t i = 0; i < chunks; i++) {
        const size_t chunkStart = i * chunkSize;
        const size_t chunkEnd = (i + 1) * chunkSize;

        result.emplace_back(bitset.begin() + chunkStart, bitset.begin() + chunkEnd);
    }

    return result;
}


