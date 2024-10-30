# SP4E: Homework 2

C++ Classes

## Table of Contents

- [Usage](#usage)
- [Output](#output)


## Installation

```
# Clone the repository
git clone https://github.com/meghshukla/SP4E.git

# Navigate to the project directory
cd SP4E/homework2/src
```

The code has a simple structure, with all files in the ```src``` directory. The main file can be produced using ```g++ main.cc series.cc -o hw2.exe```.



## Usage

The code can be run using ```./hw2.exe 1000 file ","```. Here, 1000 is the number of terms used to compute the series. The second argument can be 'file' or 'screen', where file ensures that the series is dumped into a file for plotting. Screen displays the series in the terminal. "," or "|" are some of the separators that can be used to produce psv and csv files. We include example files: ```pi.psv, natural.csv```. The corresponding plots are also made available as png files.

Example Inputs:

The case where S(x) is given to the function, and plotting is also asked. 

```./hw2.exe 1000 file ","```

```./hw2.exe 1000 file "|"```

The code also facilitates easy user interaction to produce pi, natural number and riemannian integral on the fly. Please follow the prompts on the screen for the same.

## Exercise 2.1

Thomas implemented exercise 1,2,6 and Megh did 3,4,5. The exercises 3,4,5 majorly involved Series printing/storing and fast computation whereas 2,6 majorly involved calculating the series for different functions.

## Exercise 5

1. The naive implementation is O(n^2) since it involves computing O(n) values for each n, with n increasing. Here n corresponds to the number of terms. This is shown in the compute function in ComputeArithmetic and ComputePi.

2, 3 and 4. We had previously implemented a faster process O(n) using a different method. We initialize an array called ```storedArray``` which stores the approximation involving 'i' terms at the i^th location of the array. Therefore, computing the i+1^th term is fast since it requires adding a simple computation to the value stored for the i^th term. This makes the computation linear time. However, the space complexity increases from O(1) to O(n).

5. This would still take linear time since we can precompute and store the errors starting from index N-1 all the way to index 0. Specifically, i^th term = value + (i+1)^th term. 

## Exercise 6

Explanations as comments will be added to the code for instance for the constructor and the difference in the structure of constructing computepi,sum and the integral which takes multiple inputs including a function.

The code is finalised in a manner that the user can choose either to compute the series of summation, pi , or the integral for a given function. If integral option is chosen, then the user choses among the options of the 3 functions as represented by numbers. Once the function is chosen then the code asks the user to input the limits.

6.4 : Expected values are achieved, more detailed analysis will be done as asked.

