
from scipy.optimize import fmin
from simulation_utils import readPositions, runAndComputeError

def optimizeVelocity(planet_name, input_filename, nb_steps, freq, ref_positions):
	def errorFunction(scale):
    	return runAndComputeError(scale, planet_name, input_filename, nb_steps, freq, ref_positions)
    
	initial_guess = 1.0
	optimal_scale = fmin(errorFunction, initial_guess)
	return optimal_scale

if __name__ == "__main__":
	ref_positions = readPositions('mercury', 'reference_trajectories')
	optimal_scale = optimizeVelocity('mercury', 'init.csv', 365, 1, ref_positions)
	print(f"Optimal scaling factor for Mercury's velocity: {optimal_scale}")



