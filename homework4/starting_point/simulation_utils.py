import numpy as np
import os
import subprocess

def readPositions(planet_name, directory):
	positions = []
	for i in range(365):
    	filename = os.path.join(directory, f"step-{i:04d}.csv")
    	with open(filename, 'r') as file:
        	for line in file:
            	if planet_name in line:
                	parts = line.split()
                	positions.append([float(parts[1]), float(parts[2]), float(parts[3])])
	return np.array(positions)

def computeError(positions, positions_ref):
	return np.sqrt(np.sum((positions - positions_ref) ** 2, axis=1)).sum()

def generateInput(scale, planet_name, input_filename, output_filename):
	with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
    	for line in infile:
        	if planet_name in line:
            	parts = line.split()
            	parts[4] = str(float(parts[4]) * scale)
            	parts[5] = str(float(parts[5]) * scale)
            	parts[6] = str(float(parts[6]) * scale)
            	outfile.write(' '.join(parts) + '\n')
        	else:
            	outfile.write(line)

def launchParticles(input_filename, nb_steps, freq):
	subprocess.run(['python3', 'main.py', str(nb_steps), str(freq), input_filename, 'planet', '1.0'])

def runAndComputeError(scale, planet_name, input_filename, nb_steps, freq, ref_positions):
	output_filename = 'scaled_input.csv'
	generateInput(scale, planet_name, input_filename, output_filename)
	launchParticles(output_filename, nb_steps, freq)
	positions = readPositions(planet_name, 'trajectories')
	return computeError(positions, ref_positions)




