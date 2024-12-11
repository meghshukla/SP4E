# SP4E: Homework 3

C++: Particles Codebase

## Table of Contents

- [Usage](#usage)
- [Output](#output)


## Installation

```
# Clone the repository
git clone https://github.com/meghshukla/SP4E.git

# Navigate to the project directory
cd SP4E/homework3/heat-fft-solver
```

This code requires googletest installed, a popular C++ testing framework. We recommend following the instructions in https://www.jetbrains.com/help/objc/creating-google-test-run-debug-configuration-for-test.html 

While the CMAKELists.txt file can be used to build the executable, it is highly recommended to keep the default settings in it. For instance, FFTW is highly recommended. Instructions included creating a ```build``` directory, running ``` cmake ../ ; make ```

## Usage

The following command ```./particles 5000 500 dummy.csv material_point 0.1 sine``` provides a sample way of running the executable. 5000 is the number of iterations, 500 is the frequency at which to print the intermediate temperature field, ```dummy.csv``` is a dummy file created to run the code for material_point. Since we are not adding any materials, ```circle_orbit.csv```is incompatible with the existing code. Hence, we create a dummy file consisting of ```0 0 0 0``` such that the code execution does not stop. We do not read or use this file in any manner. We choose ```material_point``` as suggested. 0.1 corresponds to the timestep and scales the gradient update. Finally, we add a new argument ```heat source``` which can be one of ```none, sine``` to simulate different heat sources.


## Exercise 1

We follow Doxyfile and its generated html files to explain the Particles codebase. Generally, the code is divided into the following Parent classes:
1. Compute
1. CsvReader/Writer
1. FFT
1. Matrix
1. ParticlesFactoryInterface
1. System
1. SystemEvolution

Multiple classes inherit from these base classes. For instance, ComputeBoundary, ComputeInteraction etc. are inherited from Compute. Different particles such as Planet, PingPoing, MaterialPoint inherit from the ParticlesFactorInterface. The code follows a Singleton design. Atmost one object can be created which inherits from ParticlesFactoryInterface. This is done by checking if the factory point is a ```nullptr``` or not. Matrix consists of various functions used to manipulate the data within matrices. FFT acts as an interface between FFTW and the Particles codebase. SystemEvolution uses System and is the heart of the code. SystemEvolution simulates the stochastic process which is numerically approximated in the method ```evolve```. 

We modify the code to accept a new argument (heat_source), complete the compute_temperature function, fill fft.hh, modify the indexing of data for all matrices (changes in matrix.hh). We additionally use SystemEvolution code to pass multiple variables to System. This is because Compute::compute accepts only *System pointers, thereby all the variables needed to compute the temperature have to be contained within System. This required adding new declarations in the System class and new methods to pass these variables from SystemEvolution to System.

## Note on Exercise 4

While we have implemented solvers for both the homogenous and sinsusoidal heat source condition, our results for the latter are off by a scaling factor. Specifically, while the temperature field after optimisation indeed follows the same trend as the given equilibrium sinusoidal, the magnitude is off by a constant scaling factor. We hypothesize that this is because FFTW does not normalize the DFT-IDFT transformation. However, we are unsure of where to implement the scaling factor. Finally, we note again that the final temperature field indeed follows a sinusoidal trend which is independent of y and a sinusoidal function of x as expected.

## Exercise 6
