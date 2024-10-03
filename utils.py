from matplotlib import pyplot as plt
import numpy as np
import argparse
import ast


def get_settings():
    plt.switch_backend('agg')
    plt.style.use('ggplot')
    plt.rcParams['figure.dpi'] = 300

    #To print out the entire matrix
    np.set_printoptions(precision=4)
    np.set_printoptions(linewidth=200)


def parse_arguments():
    parser = argparse.ArgumentParser(description='Process command line arguments.')

    # Define command line arguments
    parser.add_argument('--implementation', type=str, default="scipy")
    parser.add_argument('--algorithm', type=str, default="minimize")
    parser.add_argument('--A', type=str, default="[[8, 1], [1, 3]]")
    parser.add_argument('--b', type=str, default="[2, 4]")

    # Parse the arguments
    args = parser.parse_args()

    # Define variables from arguments
    implementation = args.implementation
    algorithm = args.algorithm

    # Safer than running eval() directly
    A = np.array(ast.literal_eval(args.A))
    b = np.array(ast.literal_eval(args.b))

    assert implementation in ['manual', 'scipy'], "Implementation must be 'manual' or 'scipy'"
    assert algorithm in ['minimize', 'lgmres'], "Algorithm must be 'minimize' or 'lmgres'"

    print('Configuration:')
    print('Implementation:', implementation)
    print('Algorithm:', algorithm)
    print('A:', A)
    print('b:', b)

    return implementation, algorithm, A, b


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


class Callback(object):
    def __init__(self, A, b):
        self.x = list()
        self.vals = list()
        self.A = A
        self.b = b

    def __call__(self, x):
        self.x.append(x)
        self.vals.append(quadratic(x, self.A, self.b))

    def set_as_array(self):
        self.x = np.array(self.x)
        self.vals = np.array(self.vals)
        print('self.x', self.x)
        print('self.vals', self.vals)