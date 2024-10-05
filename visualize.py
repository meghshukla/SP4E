import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

from utils import quadratic


def surface_plot(func_to_plot):
    """
    Plot the 3D surface for quadratic function defined by A and b.
    """
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

    # Create mesh
    X = np.arange(-10, 10, 0.1)
    Y = np.arange(-10, 10, 0.1)
    X, Y = np.meshgrid(X, Y)
    
    # Compute quadratic function
    XY = np.array([X.flatten(), Y.flatten()]).T
    Z = func_to_plot(XY).reshape(X.shape)   

    # Plot the surface.
    surface = ax.plot_surface(
        X, Y, Z, cmap=cm.coolwarm, edgecolor='none', alpha=0.5)

    # Add a color bar which maps values to colors.
    fig.colorbar(surface, shrink=0.5, aspect=5)

    return fig, ax