import matplotlib.pyplot as plt
import pandas as pd
import argparse

def plot_series(filename):
    # Determine the separator based on the file extension
    if filename.endswith('.csv'):
        separator = ','
    elif filename.endswith('.psv'):
        separator = '|'
    else:
        separator = ' '  # Default to space for .txt files

    # Read the data from the file
    data = pd.read_csv(filename, sep=separator, header=None, names=['Index', 'Value'])

    # Drop rows with NaN values in either 'Index' or 'Value' columns
    data = data.dropna(subset=['Index', 'Value'])

    # Plot the data
    plt.figure(figsize=(10, 6))
    plt.plot(data['Index'][::100], data['Value'][::100], marker='o', linestyle='-', color='b')
    plt.xlabel('Index')
    plt.ylabel('Value')
    plt.title('Series Plot')
    plt.grid(True)
    plt.savefig('plot.png')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Plot series data from a file.')
    parser.add_argument('filename', type=str, help='The name of the file to plot.')
    args = parser.parse_args()

    plot_series(args.filename)