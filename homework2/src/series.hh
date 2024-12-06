#ifndef SERIES_HH
#define SERIES_HH

#include <cmath>
#include <fstream>
#include <functional>



class Series {
public:
    // Store array of computed values
    unsigned int length;
    double* storedArray;

    Series(unsigned int length) : length(length), storedArray(new double[length]) {}
    
    virtual ~Series() {
        delete[] storedArray;
    }

    virtual double compute(unsigned int N) = 0;
    virtual double computeSeries(unsigned int N) = 0;
    virtual double getAnalyticPrediction() = 0;
};


class ComputeArithmetic : public Series{
public:

    double compute(unsigned int N) override; // Exercise 2 
    double computeSeries(unsigned int N) override; // Exercise 3
    double _computeSeries(unsigned int N);

    double getAnalyticPrediction() override {
        return 0.5 * length * (length + 1);
    }
    
    ComputeArithmetic(unsigned int N) : Series(N)
    {        
        for (int i = 0; i < length; i++){
            // Initialize stored array with NaN
            storedArray[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }
};


class ComputePi : public Series {
public:

    double compute(unsigned int N) override; // Exercise 2
    double computeSeries(unsigned int N) override; // Exercise 3
    double _computeSeries(unsigned int N); // Exercise 3

    double getAnalyticPrediction() override {
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    ComputePi(unsigned int N) : Series(N)
    {
        for (int i = 0; i < length; i++){
            // Initialize stored array with NaN
            storedArray[i] = std::numeric_limits<double>::quiet_NaN();
        }
    } 
};


class RiemannIntegral : public Series {
public:
    RiemannIntegral(double a, double b, std::function<double(double)> f, unsigned int N); 
    double compute(unsigned int N) override;
    double computeSeries(unsigned int N) override;

    double getAnalyticPrediction() override {
        return std::numeric_limits<double>::quiet_NaN();
    }

private:
    double a; // Lower limit of the integral
    double b; // Upper limit of the integral
    std::function<double(double)> f; // Function to integrate
};

#endif
