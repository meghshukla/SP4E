// src/series.cc
#include "series.hh"


double ComputeArithmetic::compute(unsigned int N) {
    double sum = 0;
    for (unsigned int k = 1; k <= N; ++k) {
        sum += k;
    }
    return sum;
}

// Recursive implementation of the series
double ComputeArithmetic::_computeSeries(unsigned int N) {
    
    // Check if the value has to be computed
    if (std::isnan(this->storedArray[N-1])) {
        if (N == 1) {
            this->storedArray[N-1] = 1;
        }
        else {
            this->storedArray[N-1] = N + _computeSeries(N - 1);
        }
        return this->storedArray[N-1];
    }
    // Value has already been computed
    else {
        return this->storedArray[N-1];
    }
}

double ComputeArithmetic::computeSeries(unsigned int N) {
    for (int i = 1; i <= N; i++){
        _computeSeries(N);
    }
    return this->storedArray[N-1];
}


double ComputePi::compute(unsigned int N) {
    double sum = 0;
    for (unsigned int k = 1; k <= N; ++k) {
        sum += 1.0 / (k * k);
    }
    return std::sqrt(6 * sum);
}

// Recursive implementation of the series
double ComputePi::_computeSeries(unsigned int N) {

    // Check if the value has to be computed
    if (std::isnan(this->storedArray[N-1])) {
        if (N == 1) {
            this->storedArray[N-1] = 1;
        }
        else {
            this->storedArray[N-1] = (1.0 / std::pow(N, 2)) + _computeSeries(N - 1);
        }
        return this->storedArray[N-1];
    }
    // Value has already been computed
    else {
        return this->storedArray[N-1];
    }
}

double ComputePi::computeSeries(unsigned int N) {
    for (int i = 1; i <= N; i++){
        _computeSeries(N);
    }
    for (int i = 1; i <= N; i++){
        this->storedArray[i-1] = std::sqrt(6 * this->storedArray[i-1]);
    }
    return this->storedArray[N-1];
}


// Constructor for RiemannIntegral
RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f, unsigned int N) : a(a), b(b), f(f), Series(N) {}

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

double RiemannIntegral::computeSeries(unsigned int N) {
    return compute(N);
}