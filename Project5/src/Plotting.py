import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

potential_file = 'Potential.csv'
P_file = 'P.csv'
U_real_file = 'U_Real.csv'
U_imag_file = 'U_imag.csv'


pot_data = pd.read_csv(potential_file, header=None)
max_pot = np.max(pot_data)
P = pd.read_csv(P_file, header = None)      # P is 2D
U_real = pd.read_csv(U_real_file, header = None)      # P is 2D
U_imag = pd.read_csv(U_imag_file, header = None)      # P is 2D

P = P.values
U_real = U_real.values
U_imag = U_imag.values

rows, cols = P.shape
M_2 = int(np.sqrt(rows))
timesteps = cols

# Reshape the 2D array into a 3D array
P = P.reshape((M_2, M_2, timesteps)) 
U_real = U_real.reshape((M_2, M_2, timesteps)) 
U_imag = U_imag.reshape((M_2, M_2, timesteps)) 


def plot_potential():
    plt.figure(figsize=(10, 10))
    sns.heatmap(pot_data, cmap='viridis', square=True)
    plt.title('Heatmap of Matrix')
    plt.xlabel('X axis')
    plt.ylabel('Y axis')
    plt.legend()
    plt.show()
# plot_potential()

def plot_three_times(data):
    'data is either P, U_real, or U_imag'
    t_3_id = [0, int(timesteps / 2), timesteps - 1]
    for i in t_3_id:
        plt.figure(figsize=(10, 10))
        # sns.heatmap(pot_data / (max_pot), cmap='viridis', square=True, label = f'Potential = {max_pot}') #Normalized potential. doesn't quite work
        sns.heatmap(data[:,:,i], cmap='viridis', square=True, label = f'Wavefunction') 
        plt.title('Heatmap of Matrix')
        plt.xlabel('X axis')
        plt.ylabel('Y axis')
        plt.legend()
        plt.show()
plot_three_times(P)