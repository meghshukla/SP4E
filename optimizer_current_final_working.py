import argparse
import numpy as np
from scipy.optimize import minimize
from scipy.sparse.linalg import lgmres

def minimize_function(S_str):
    # Define the function S(x) to minimize
    def S(x):
        return eval(S_str, {"np": np, "x": x})

    # Initial guess for x
    x0 = np.zeros(2)  # Modify size based on your problem

    # Define the callback to track intermediate steps
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x

    # Minimize S(x) with callback
    result = minimize(S, x0, callback=callback)
    
    # Return the result, the value of S(x) at the solution, and the callback values
    return result.x, S(result.x), callback

def solve_lgmres(A, b):
    # Define the callback to track intermediate steps
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x

    # Initial guess for x
    x0 = np.zeros(len(b))  # Modify based on b size

    # Solve the system using lgmres with callback
    solution, _ = lgmres(A, b, x0=x0, callback=callback, atol=0.0)  # Set atol to 0.0
    
    # Return the solution, Ax, and the callback values
    Ax = np.dot(A, solution)  # Calculate Ax
    return solution, Ax, callback

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
        x, S_x, callback = minimize_function(args.function)
        print(f"Minimized x: {x}")
        print(f"S(x) at the solution: {S_x}")
    
    elif args.A and args.b:
        # If A and b are provided, solve Ax = b
        A = eval(args.A, {"np": np})
        b = eval(args.b, {"np": np})
        x, Ax, callback = solve_lgmres(A, b)
        print(f"Solution x: {x}")
        print(f"Ax at the solution: {Ax}")
    
    else:
        print("Error: Either provide a function to minimize or A and b to solve Ax = b.")
