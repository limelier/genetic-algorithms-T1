#ifndef T1_PROJECT_UTIL_BITSETFUNCS_H_
#define T1_PROJECT_UTIL_BITSETFUNCS_H_

#include <cstddef>
#include <vector>

std::size_t bitsetSize(double lower, double upper, int precision);
std::vector<bool> generateBitset(size_t size);
std::vector<std::vector<bool>> generateNeighbors(std::vector<bool>& bitset);
double bitsetToDouble(const std::vector<bool>& bitset, size_t bits, double lower, double upper);

#endif //T1_PROJECT_UTIL_BITSETFUNCS_H_
