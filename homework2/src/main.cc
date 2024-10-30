// src/main.cc
#include <iostream>
#include <sstream>
#include <memory>
#include "series.hh"
#include "dumper_series.hh"

int main(int argc, char* argv[]) {

    // Should take in only threee arguments
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <N> <output_mode> [separator]" << std::endl;
        return 1;
    }

    unsigned int N;
    std::string output_mode;
    char separator = ' ';

    // Concatenate arguments and unstack them to variables
    std::stringstream ss;
    for (int i = 1; i < argc; ++i) {
        ss << argv[i] << " ";
    }
    ss >> N >> output_mode >> separator;

    int choice;

    std::cout << "Choose a series to compute:" << std::endl;
    std::cout << "1. Sum of integers up to N (ComputeArithmetic)" << std::endl;
    std::cout << "2. Approximation of pi (ComputePi)" << std::endl;
    std::cout << "3. Riemann Integral" << std::endl;
    std::cout << "Enter choice (1, 2, or 3): ";
    std::cin >> choice;

    std::unique_ptr<Series> series;

    // Allocate the correct derived class based on user choice
    if (choice == 1) {
        series = std::make_unique<ComputeArithmetic>(N);
    }
    else if (choice == 2) {
        series = std::make_unique<ComputePi>(N);
    }
    else if (choice == 3) {
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

        series = std::make_unique<RiemannIntegral>(a, b, f, N);

    }
    else {
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }

    // Call compute on the chosen series and output the result
    double result = series->compute(N);
    std::cout << "Result with N = " << N << " is: " << result << std::endl;

    if (choice != 3) {
        double resultSeries = series->computeSeries(N);    
        std::cout << "Result with N (improved complexity) = " << N << " is: " << resultSeries << std::endl;
        
        // Print Series
        if (output_mode == "screen") {
            PrintSeries printSeries = PrintSeries(*series, 5);
            printSeries.dump(std::cout);
        }

        // Write Series
        else if (output_mode == "file") {
            WriteSeries writer(*series, N);

            // Set separator and dump to file
            writer.setSeparator(separator);
            std::ofstream outFile("output.txt");
            if (!outFile) {
                std::cerr << "Error opening file: output.txt" << std::endl;
                return 1;
            }
            outFile << writer;
            outFile.close();
        }
        else {
            std::cerr << "Invalid output mode." << std::endl;
            return 1;
        }
    }

    return 0;
}







