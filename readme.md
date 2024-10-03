# SP4E: Homework 1

Optimization using GMRES and Scipy's inbuilt functions

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Output](#output)


## Installation

```
# Clone the repository
git clone https://github.com/meghshukla/SP4E.git

# Navigate to the project directory
cd SP4E

# Install dependencies
pip install -r requirements.txt
```

The code has a simple structure, with all files in the same directory. The main file is called ```optimizer.py``` which calls the minimizer and plots the convergence process. We have our custom implementation in ```gmres.py```. The file ```visualize.py``` contains the function to plot the optimization surface. We house miscellaneous functions in ```utils.py```. In ```requirements.txt```, we store the libraries needed to execure the code.


## Usage

We provide a manual implementation of GMRES and scipy's inbuilt functions.
In addition, we provide tools to plot convergence.
Finally, A and b which are used to define the quadratic form can also be given as command line input.

Example:
```python optimizer.py --implementation manual --algorithm lgmres --plot 1```

The defaults are:
1. ```implementation: {manual OR scipy} (default: scipy)```
2. ```algorithm: {minimize OR lgmres} (default: minimize)```
3. ```plot: {0 or 1} (default: 1) ```
4. ```A: <list of lists> (default: [[8, 1], [1, 3]])```
5. ```b: <list> (default: [2, 4])```

## Output

We save a matplotlib plot containing the optimization surface, trajectory of the point, and optimized value. An example plot is in this repository with the name: ```manual_lgmres.png```