"""This guide was very helpful
https://acme.byu.edu/00000179-aa18-d402-af7f-abf806ac0001/gmres2020-pdf"""

import numpy as np


def dot(A, B):
    return np.einsum('i, i->', A, B)

def mul(A, B):
    return np.einsum('i, i->i', A, B)

def matmul(A, B):
    return np.einsum('ij, jk -> ik', A, B)

def matrix_norm(A):
    square = np.einsum('ij, ij->ij', A, A)
    return np.einsum('ij->', square) ** 0.5

def vector_norm(A):
    square = np.einsum('i, i->i', A, A)
    return np.einsum('i->', square) ** 0.5
    



def solve(A, b, x0, callback, k=10, tol=1e-6):
    """
    Solve the system Ax = b using the GMRES algorithm.
    
    Parameters:
    A (numpy.ndarray): The matrix A.
    b (numpy.ndarray): The vector b.
    x0 (numpy.ndarray): The initial guess for x.
    k (int): The number of iterations.
    tol (float): The tolerance for the residual.
    
    Returns:
    x (numpy.ndarray): The solution to the system.
    """
    n = A.shape[0]
    Q = np.zeros((n, k+1))
    H = np.zeros((k+1, k))

    # Residual terrm
    r = b - matmul(A, x0[..., None]).squeeze()
    Q[:, 0] = r / vector_norm(r)
    
    # Arnoldi iteration
    for j in range(k):
        #print(j)
        Q[:, j+1] = matmul(A, Q[:, j][..., None]).squeeze()
        for i in range(j+1):
            H[i, j] = dot(Q[:, i], Q[:, j+1])
            Q[:, j+1] = Q[:, j+1] - H[i, j] * Q[:, i]
        
        H[j+1, j] = vector_norm(Q[:, j+1])
        if abs(H[j+1, j]) > tol:
            Q[:, j+1] = Q[:, j+1] / H[j+1, j]
        
        e1 = np.zeros(j+2)
        e1[0] = vector_norm(r)
        y = np.linalg.lstsq(H[:j+2, :j+1], e1, rcond=None)[0]

        res = vector_norm(matmul(H[:j+2, :j+1], y[..., None]).squeeze() - e1)

        # Store to plot trajectory later
        callback(x0 + matmul(Q[:, :j+1], y[..., None]).squeeze())

        if res < tol:
            return x0 + matmul(Q[:, :j+1], y[..., None]).squeeze(), 0   
        
    return x0 + matmul(Q[:, :j+1], y[..., None]).squeeze(), 1