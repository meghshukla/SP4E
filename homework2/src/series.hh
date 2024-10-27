// src/series.hh
#ifndef SERIES_HH
#define SERIES_HH

#include <cmath> // for sqrt

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

#endif
