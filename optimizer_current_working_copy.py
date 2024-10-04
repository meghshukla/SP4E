import argparse
import numpy as np
from scipy.optimize import minimize
from scipy.sparse.linalg import lgmres

def minimize_function(S_str):
    # Define the function S(x) to minimize
    def S(x):
        # Safely evaluate the function string in the given context
        return eval(S_str, {"np": np, "x": x})
    
    # For demonstration, we assume the size of x from the function (you can modify this)
    x0 = np.zeros(2)  # Initial guess for x (assuming the problem size)
    
    # Minimize S(x)
    result = minimize(S, x0)
    return result.x

def solve_lgmres(A, b, x0=None, callback=None):
    # Solve the system using lgmres
    if x0 is None:
        x0 = np.zeros(len(b))  # Initial guess
    solution, info = lgmres(A, b, x0=x0, callback=callback, atol=0.0)
    return solution

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Minimize a function S(x) or solve Ax = b using lgmres.")
    
    # Input for the function as a string
    parser.add_argument("function", type=str, nargs="?", default=None,
                        help="The function S(x) to minimize as a string. Example: '0.5 * np.dot(x.T, np.dot(np.array([[8, 1], [1, 3]]), x)) - np.dot(np.array([2, 4]), x)'")
    
    # Input for A and b as numpy arrays (optional if solving Ax=b)
    parser.add_argument("--A", type=str, help="Matrix A as a numpy array string. Example: 'np.array([[8, 1], [1, 3]])'")
    parser.add_argument("--b", type=str, help="Vector b as a numpy array string. Example: 'np.array([2, 4])'")
    
    args = parser.parse_args()  

    if args.function:
        # If function is provided, minimize it
        x = minimize_function(args.function)
        print("Minimized x:", x)
    
    elif args.A and args.b:
        # If A and b are provided, solve Ax = b
        A = eval(args.A, {"np": np})
        b = eval(args.b, {"np": np})
        x = solve_lgmres(A, b)
        print("Solution to Ax = b:", x)
    
    else:
        print("Error: Either provide a function to minimize or A and b to solve Ax = b.")
