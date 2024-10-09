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

The code has a simple structure, with all files in the same directory. The main file is called ```optimizer.py``` which calls the minimizer and plots the convergence process. We have our custom implementation in ```gmres.py```. The file ```visualize.py``` contains the function to plot the optimization surface. We house miscellaneous functions in ```utils.py```. In ```requirements.txt```, we store the libraries needed to execute the code.


## Usage

We provide a manual implementation of GMRES and scipy's inbuilt functions.
In addition, we provide tools to plot convergence.

The function can either take function-functor whose form is determined by the user and inputted in the command-prompt in a string form, or can take array variables of A and b also as separate strings. In the former the program assumes the user wants to find the minimum of a function and implements the appropriate scheme, while in the latter it assumes the user is asking for the solution of the system of equations of Ax=b.

In the option Ax=b, i.e., providing A and b instead of S(x), the program also than asks for the type of solution algorithm to be implemented among two options 'scipy' and 'manual'. The 'scipy' uses the python built-in function of lgmres, while the 'manual' option solves the system with the ```gmres.py```.

The plotting is optional, and determined by the user input. 

Example Inputs:

The case where S(x) is given to the function, and plotting is also asked. 

```python optimizer.py "0.5 * np.dot(x.T, np.dot(np.array([[8, 1], [1, 3]]), x)) - np.dot(np.array([2, 4]), x)" --plot```

The case where S(x) is given to the function, and plotting is supressed. 

```python optimizer.py "0.5 * np.dot(x.T, np.dot(np.array([[8, 1], [1, 3]]), x)) - np.dot(np.array([2, 4]), x)"```

The case where A and b are given to the function. The A array is inputted after --A, and the arrray b is inputted after b. Then the solution approach is prescribed by the user after the "--solution". The user can choose either manual or scipy as explained above, the examples are given below:

```python optimizer.py --A "np.array([[8, 1], [1, 3]])" --b "np.array([2, 4])" --solution manual --plot```

```python optimizer.py --A "np.array([[8, 1], [1, 3]])" --b "np.array([2, 4])" --solution scipy --plot```

## Output

We save a matplotlib plot containing the optimization surface, trajectory of the point, and optimized value. An example plot is in this repository with the name: ```manual_gmres.png``` 

As can be seen, when we compare the plots for the case when the scipy optimisation methods is used ("minimize") and the case when the gmres algorithm is used, the latter is more efficient and faster in finding the optimal solution as it takes less steps to reach the solution.
