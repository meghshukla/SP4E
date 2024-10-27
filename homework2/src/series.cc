// src/series.cc
#include "series.hh"

double ComputeArithmetic::compute(unsigned int N) {
    double sum = 0;
    for (unsigned int k = 1; k <= N; ++k) {
        sum += k;
    }
    return sum;
}

double ComputePi::compute(unsigned int N) {
    double sum = 0;
    for (unsigned int k = 1; k <= N; ++k) {
        sum += 1.0 / (k * k);
    }
    return std::sqrt(6 * sum);
}
