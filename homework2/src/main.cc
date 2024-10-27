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


unsigned int N = 1000; // Example value for N
    int choice;

    std::cout << "Choose a series to compute:" << std::endl;
    std::cout << "1. Sum of integers up to N (ComputeArithmetic)" << std::endl;
    std::cout << "2. Approximation of pi (ComputePi)" << std::endl;
    std::cout << "Enter choice (1 or 2): ";
    std::cin >> choice;

    // Base class pointer
    Series* series = nullptr;

    // Allocate the correct derived class based on user choice
    if (choice == 1) {
        series = new ComputeArithmetic();
    } else if (choice == 2) {
        series = new ComputePi();
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







