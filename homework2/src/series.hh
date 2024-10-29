// src/series.hh
#ifndef SERIES_HH
#define SERIES_HH

#include <cmath> // for sqrt
#include <functional> // For std::function

class Series {
public:
    virtual double compute(unsigned int N) = 0;
};

class ComputeArithmetic : public Series {
public:
    double compute(unsigned int N) override;
};

class ComputePi : public Series {
public:
    double compute(unsigned int N) override;
};


class RiemannIntegral : public Series {
public:
    RiemannIntegral(double a, double b, std::function<double(double)> f);
    double compute(unsigned int N) override;

private:
    double a; // Lower limit of the integral
    double b; // Upper limit of the integral
    std::function<double(double)> f; // Function to integrate
};



#endif
