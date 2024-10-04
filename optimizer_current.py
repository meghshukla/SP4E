import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import minimize
from scipy.sparse.linalg import lgmres
import argparse

from utils import parse_arguments, get_settings, quadratic, Callback
from visualize import surface_plot
import gmres



parser = argparse.ArgumentParser(description="Minimize a function S(x) or solve Ax = b using lgmres.")

# Input for the function as a string
parser.add_argument("function", type=str, nargs="?", default=None,
                    help="The function S(x) to minimize as a string. Example: '0.5 * np.dot(x.T, np.dot(np.array([[8, 1], [1, 3]]), x)) - np.dot(np.array([2, 4]), x)'")

# Input for A and b as numpy arrays (optional if solving Ax=b)
parser.add_argument("--A", type=str, help="Matrix A as a numpy array string. Example: 'np.array([[8, 1], [1, 3]])'")
parser.add_argument("--b", type=str, help="Vector b as a numpy array string. Example: 'np.array([2, 4])'")

args = parser.parse_args()  

def minimize_function(args):

    global implementation
    global algorithm 


    if args.function:
    
        # that means the user is asking for function minimisation. Thus for the visualisation module to work appropriately as written by my co-worker I define the necessary variables
        implementation ='scipy' 
        algorithm ='minimize'
    
        def S(x):
            return eval(args.function, {"np": np, "x": x})
        
        
        callback_values = []
        def callback(xk):
            callback_values.append(np.copy(xk))  # Save intermediate values of x
            
        x0 = np.zeros(2)  # Modify size based on your problem
    
    
        # Minimize S(x) with callback
        result = minimize(S, x0, callback=callback)
        x = result.x
        value=S(x)
        success = result.success
        
        print(f"Minimized x: {x}")
        print(f"S(x) at the solution: {S(x)}")
        
        
    
    elif args.A and args.b:
        
        
        # that means the user is asking for the solution of the linear system of equation. Thus for the visualisation module to work appropriately as written by my co-worker I define the necessary variables
        implementation ='scipy' 
        algorithm ='lgmres'
        
        
        # If A and b are provided, solve Ax = b
        A = eval(args.A, {"np": np})
        b = eval(args.b, {"np": np})
    

        callback_values = []
        def callback(xk):
            callback_values.append(np.copy(xk))  # Save intermediate values of x
        
        # Initial guess for x
        x0 = np.zeros(len(b))  # Modify based on b size
    
        solution, info = lgmres(A, b, x0=x0, callback=callback, atol=0.0)
        x=solution
        
        if info == 0:
            success = 1  # Success when info == 0 (convergence)
        else:
            success = 0  # Failure when info != 0 (no convergence)
        value = np.dot(A, x) - b     
        
    else:
        raise Exception("Invalid choice of implementation or algorithm.")    
    
    return (x, success), value, callback




minimization, val, callback = minimize_function(args)
x, success = minimization


if success:
    print("Successful convergence")
else:
    print("Convergence failed, giving approximate solution")

print("Minimizer: {}\tValue: {}".format(x, val))



   

# The plotting the function based on the type of arguments passed by argparse,
# we define the function to be plotted accordingly.



