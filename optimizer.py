import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import minimize
from scipy.sparse.linalg import lgmres

from utils import parse_arguments, get_settings, quadratic, Callback
from visualize import surface_plot
import gmres


get_settings()
implementation, algorithm, A, b, plot = parse_arguments()


def minimize_function(implementation, algorithm, A, b):
    """
    Function to minimize S(x) = 0.5 (x^T A x) - x^T b using scipy.optimize.minimize
    with callback to track intermediate steps.
    
    Parameters:
    A (numpy.ndarray): The matrix A.
    b (numpy.ndarray): The vector b.
    
    Returns:
    1. Tuple containing the optimized value and success status.
    2. Value of the objective function at the minimizer.
    3. Callback object to track intermediate steps.
    """
    # Define the callback function
    callback = Callback(A, b)
    
    # Initial guess for x (eight)
    x0 = np.zeros(b.shape) + 8.

    # Minimize the objective function S(x) with callback to track iterations
    if implementation == 'scipy' and algorithm == 'minimize':
        result = minimize(quadratic, x0, args=(A, b), callback=callback)
        x = result.x
        success = result.success
    
    elif implementation == 'scipy' and algorithm == 'lgmres':
        solution = lgmres(A, b, x0=x0, callback=callback)
        x = solution[0]
        success = (solution[1] == 0)

    elif implementation == 'manual' and algorithm == 'lgmres':
        solution = gmres.solve(A, b, x0=x0, callback=callback)
        x = solution[0]
        success = (solution[1] == 0)
    
    else:
        raise Exception("Invalid choice of implementation or algorithm.")
    
    return (x, success), quadratic(x, A, b), callback

minimization, val, callback = minimize_function(implementation, algorithm, A, b)
x, success = minimization


if success:
    print("Successful convergence")
else:
    print("Convergence failed, giving approximate solution")

print("Minimizer: {}\tValue: {}".format(x, val))


# Plot the surface
if plot:
    fig, ax = surface_plot(A, b)
    # Plot the minimizer as a red dot
    ax.scatter(x[0], x[1], val, color='red', s=100, label="Minimizer")

    # Plot the trajectory in blue
    callback.set_as_array()
    ax.scatter(callback.x[:, 0], callback.x[:, 1], callback.vals, color='blue', s=50, label="Iterations")
    ax.plot(callback.x[:, 0], callback.x[:, 1], callback.vals, color='blue', linewidth=2)
    ax.legend()
    plt.title("Implementation: {}, Algorithm: {}".format(implementation, algorithm))
    plt.savefig('{}_{}.png'.format(implementation, algorithm), bbox_inches="tight")
