import numpy as np

def generate_reference_frequencies(size, filename):
    with open(filename, "w") as file:
        for i in range(size):
            freq_x = i if i <= size // 2 else i - size
            for j in range(size):
                freq_y = j if j <= size // 2 else j - size
                file.write(f"{freq_x},{freq_y}\n")

# Save in the root directory
generate_reference_frequencies(8, "frequencies_reference.txt")
