import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import minimize
from scipy.sparse.linalg import lgmres

from utils import quadratic, parse_arguments
from visualize import surface_plot
import gmres

args = parse_arguments()
    
# Assign the value of the "plot" variable
plot = args.plot  # This will be True if --plot is provided, False otherwise

if args.function:  # this is the case where the user provides a function.

    def S(x):
        if len(x.shape) > 1:  # Check if we have a 2D array of points
            return np.array([eval(args.function, {"np": np, "x": xi}) for xi in x])
        else:
            return eval(args.function, {"np": np, "x": x})      
        
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x
        
    x0 = np.zeros(2)  # Initial guess for the minimization algorithm


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
    
    

elif args.A and args.b:  # this is the case where the user provides A and b

        
    # If A and b are provided, solve Ax = b
    A = eval(args.A, {"np": np})
    b = eval(args.b, {"np": np})
    
    
    callback_values = []
    def callback(xk):
        callback_values.append(np.copy(xk))  # Save intermediate values of x
    
    x0 = np.zeros(len(b)) # Initial guess for the minimization algorithm
    
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
         
    val = np.dot(A, x) - b # this is the value, i.e, the residual attained for the solution x.
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


