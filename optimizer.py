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

# Option for choosing solution method when A and b are provided ('scipy' or 'manual')
parser.add_argument("--solution", type=str, choices=['scipy', 'manual'], help="Choose the solution method: 'scipy' or 'manual'")

# Add an option to ask the user if they want to plot the results
parser.add_argument("--plot", action="store_true", help="If provided, the results will be plotted")

args = parser.parse_args()  

# Assign the value of the "plot" variable
plot = args.plot  # This will be True if --plot is provided, False otherwise

if args.function:

    def S(x):
        if len(x.shape) > 1:  # Check if we have a 2D array of points
            return np.array([eval(args.function, {"np": np, "x": xi}) for xi in x])
        else:
            return eval(args.function, {"np": np, "x": x})      
        
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x
        
    x0 = np.zeros(2)  # Modify size based on your problem


    # Minimize S(x) with callback
    result = minimize(S, x0, callback=callback)
    x = result.x
    val=S(x)
    success = result.success
    
    # definining the function to be plotted which will be fed to visualisation module.
    plot_func=S
    
    print(f"Minimized x: {x}")
    print(f"S(x) at the solution: {S(x)}")
    
    # below the variables are of "implementation" and "algorithm" are assigned their associated strings
    #according to the plotting function and naming convention implemented by my co-worker.
    implementation='scipy'
    algorithm='minimize'
    
    

elif args.A and args.b:
        
    # If A and b are provided, solve Ax = b
    A = eval(args.A, {"np": np})
    b = eval(args.b, {"np": np})
    
    
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x
    
    # Initial guess for x
    x0 = np.zeros(len(b))  # Modify based on b size
    
    # here, based on the solution approached asked by the user, we implement the algorithm
    
    if args.solution == 'scipy':

        solution, info = lgmres(A, b, x0=x0, callback=callback, atol=0.0)
        x=solution
        
        
        if info == 0:
            success = 1  # Success when info == 0 (convergence)
        else:
            success = 0  # Failure when info != 0 (no convergence)
     
        # below the variables are of "implementation" and "algorithm" are assigned their associated strings
        #according to the plotting function and naming convention implemented by my co-worker.
        implementation='scipy'
        algorithm='lgmres'
            
            
    elif args.solution == 'manual':
            
        solution = gmres.solve(A, b, x0=x0, callback=callback)
        x = solution[0]
        success = (solution[1] == 0)     
        
        # below the variables are of "implementation" and "algorithm" are assigned their associated strings
        #according to the plotting function and naming convention implemented by my co-worker.
        implementation='manual'
        algorithm='gmres'
         
    val = np.dot(A, x) - b 
    plot_func = lambda x: quadratic(x, A, b) # defining the plotting function using lambda so that the "quadratic" function takes x as a variable.
    
else:
    raise Exception("Invalid choice of implementation or algorithm.")    


if success:
    print("Successful convergence")
else:
    print("Convergence failed, giving approximate solution")

print("Minimizer: {}\tValue: {}".format(x, val))


# Plot the surface
if plot:
    fig, ax = surface_plot(plot_func)

    # Convert callback_values to an array for plotting
    callback_array = np.array(callback_values)
    
    # Plot the minimizer as a red dot
    ax.scatter(x[0], x[1], color='red', s=100, label="Minimizer")
    # Plot the trajectory in blue
    if len(callback_array) > 0:
        ax.scatter(callback_array[:, 0], callback_array[:, 1], color='blue', s=50, label="Iterations")
        ax.plot(callback_array[:, 0], callback_array[:, 1], color='blue', linewidth=2)

    ax.legend()
    plt.title("Implementation: {}, Algorithm: {}".format(implementation, algorithm))
    plt.savefig('{}_{}.png'.format(implementation, algorithm), bbox_inches="tight")
    plt.show()


