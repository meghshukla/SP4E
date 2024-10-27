import numpy as np
import argparse


def parse_arguments():
    """
    Read command line arguments
    """
    
    parser = argparse.ArgumentParser(description="Minimize a function S(x) or solve Ax = b using lgmres.")
    
    # Input for the function as a string (the option for minimizing the function S(x))
    parser.add_argument("function", type=str, nargs="?", default=None,
                        help="The function S(x) to minimize as a string. Example: '0.5 * np.dot(x.T, np.dot(np.array([[8, 1], [1, 3]]), x)) - np.dot(np.array([2, 4]), x)'")
    
    # Input for A and b as numpy arrays (the option for solving Ax=b)
    parser.add_argument("--A", type=str, help="Matrix A as a numpy array string. Example: 'np.array([[8, 1], [1, 3]])'")
    parser.add_argument("--b", type=str, help="Vector b as a numpy array string. Example: 'np.array([2, 4])'")
    
    # Option for choosing solution method when A and b are provided ('scipy' or 'manual')
    parser.add_argument("--solution", type=str, choices=['scipy', 'manual'], help="Choose the solution method: 'scipy' or 'manual'")
    
    # Adding an option to ask the user if they want to plot the results
    parser.add_argument("--plot", action="store_true", help="If provided, the results will be plotted")
    
    args = parser.parse_args()  

    return args

def quadratic(x, A, b):
    """
    Calculates the value of the quadratic function
    x: variable to minimize. x.shape = (batch, 2) or (2,)
    A: matrix. A.shape = (2, 2)
    b: vector. b.shape = (2,)
    """
    
    if x.shape == (2,):
        x = x[None, :]

    xA = np.einsum('Bi, ij->Bj', x, A)
    xAx = np.einsum('Bj, Bj->B', xA, x)
    
    bx = np.einsum('Bi, i->B', x, b)

    value = (0.5 * xAx) - bx
    return value.squeeze()
