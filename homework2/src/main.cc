// src/main.cc
#include <iostream>
#include "series.hh"

int main() {



/* the code below is the implementation of 2.2-2.5 

    // Testing ComputePi
    ComputePi SeriesPi;
    unsigned int N = 1000; // Example value for N
    double piResult = SeriesPi.compute(N);
    std::cout << "Approximation of pi with N = " << N << " is: " << piResult << std::endl;

    // Testing ComputeArithmetic
    ComputeArithmetic SeriesArithmetic;
    double arithmeticResult = SeriesArithmetic.compute(N);
    std::cout << "Sum of integers up to N = " << N << " is: " << arithmeticResult << std::endl;


// end of 2.2-2.5 

*/



// the code below is the implementation of 2.6


unsigned int N = 100000; // Example value for N
    int choice;

    std::cout << "Choose a series to compute:" << std::endl;
    std::cout << "1. Sum of integers up to N (ComputeArithmetic)" << std::endl;
    std::cout << "2. Approximation of pi (ComputePi)" << std::endl;
    std::cout << "3. Riemann Integral" << std::endl;
    std::cout << "Enter choice (1, 2, or 3): ";
    std::cin >> choice;

    // Base class pointer
    Series* series = nullptr;

    // Allocate the correct derived class based on user choice
    if (choice == 1) {
        series = new ComputeArithmetic();
    } else if (choice == 2) {
        series = new ComputePi();
    } else if (choice == 3) {
        double a, b;
        int func_choice;

        std::cout << "Choose the function for integration:" << std::endl;
        std::cout << "1. f(x) = x^3" << std::endl;
        std::cout << "2. f(x) = cos(x)" << std::endl;
        std::cout << "3. f(x) = sin(x)" << std::endl;
        std::cout << "Enter function choice (1, 2, or 3): ";
        std::cin >> func_choice;

        std::cout << "Enter lower limit a: ";
        std::cin >> a;
        std::cout << "Enter upper limit b: ";
        std::cin >> b;


        std::function<double(double)> f;
        if (func_choice == 1) {
            f = [](double x) { return x * x * x; };
        } else if (func_choice == 2) {
            f = [](double x) { return std::cos(x); };
        } else if (func_choice == 3) {
            f = [](double x) { return std::sin(x); };
        } else {
            std::cout << "Invalid function choice." << std::endl;
            return 1;
        }

        series = new RiemannIntegral(a, b, f);

    } else {
    std::cout << "Invalid choice." << std::endl;
    return 1;
    }


    // Call compute on the chosen series and output the result
    double result = series->compute(N);
    std::cout << "Result with N = " << N << " is: " << result << std::endl;

    // Clean up dynamically allocated memory
    delete series;

    return 0;
}







