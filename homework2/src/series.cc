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

// Constructor for RiemannIntegral
RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f)
    : a(a), b(b), f(f) {}

// Compute method for RiemannIntegral using Riemann sum
double RiemannIntegral::compute(unsigned int N) {
    double delta_x = (b - a) / N;
    double sum = 0;
    for (unsigned int i = 1; i <= N; ++i) {
        double x_i = a + i * delta_x;
        sum += f(x_i) * delta_x;
    }
    return sum;
}