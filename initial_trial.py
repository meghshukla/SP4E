import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from optimizer import minimize_function  # Import the optimizer function

# Define matrix A and vector b
A  = np.array([[8, 1], [1, 3]])
b = np.array([2, 4])

# Store iteration steps
iteration_steps = []

def callback(xk):
    """
    Callback function to capture the solution at each iteration step.
    
    Parameters:
    xk (numpy.ndarray): The current solution.
    """
    iteration_steps.append(np.copy(xk))

def S(x1, x2):
    x = np.array([x1, x2])
    return x.T @ A @ x - x.T @ b

# Generate x1 and x2 values
x1_vals = np.linspace(-6, 6, 100)
x2_vals = np.linspace(-6, 6, 100)
X1, X2 = np.meshgrid(x1_vals, x2_vals)

# Compute S(x1, x2) for each point in the grid
S_vals = np.array([[S(x1, x2) for x1, x2 in zip(x1_row, x2_row)] for x1_row, x2_row in zip(X1, X2)])

# Now use the optimizer to find the minimizer and track iterations
x_min, result = minimize_function(A, b, callback=callback)
print("Minimizer:", x_min)
print("Optimization Result:", result)

# Compute the value of S at the minimizer for plotting
S_min = S(x_min[0], x_min[1])

# Create a surface plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the surface
ax.plot_surface(X1, X2, S_vals, cmap='viridis', alpha=0.8)

# Plot the minimizer as a red dot
ax.scatter(x_min[0], x_min[1], S_min, color='red', s=100, label="Minimizer")

# Plot the points at each iteration in blue and connect them with a line
steps_x = [step[0] for step in iteration_steps]
steps_y = [step[1] for step in iteration_steps]
steps_z = [S(step[0], step[1]) for step in iteration_steps]

# Plot each iteration step as blue points
ax.scatter(steps_x, steps_y, steps_z, color='blue', s=50, label="Iterations")

# Draw a line connecting the iteration points
ax.plot(steps_x, steps_y, steps_z, color='blue', linewidth=2)

# Set labels
ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('S(x)')

# Add a legend
ax.legend()

# Show the plot
plt.show()

# Plot iteration progress in 2D
fig, ax2d = plt.subplots()
ax2d.contour(X1, X2, S_vals, levels=50, cmap='viridis')

# Plot intermediate solutions
ax2d.plot(steps_x, steps_y, 'bo-', label='Iterations')

# Highlight minimizer
ax2d.scatter(x_min[0], x_min[1], color='red', s=100, label="Minimizer")

# Set labels
ax2d.set_xlabel('x1')
ax2d.set_ylabel('x2')

# Add a legend
ax2d.legend()

# Show the plot
plt.show()
