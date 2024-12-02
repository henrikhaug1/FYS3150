import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

potential_file = 'Potential.csv'
P_file = 'P.csv'

pot_data = pd.read_csv(potential_file, header=None)
max_pot = np.max(pot_data)
P = pd.read_csv(P_file, header = None)      # P is 2D
P = P.values

rows, cols = P.shape

M_2 = int(np.sqrt(rows))

timesteps = cols

# Reshape the 2D array into a 3D array
P = P.reshape((M_2, M_2, timesteps)) 

t_3_id = [1, int(timesteps / 2), timesteps - 1]

for i in t_3_id:
    plt.figure(figsize=(10, 10))
    # sns.heatmap(pot_data / (max_pot), cmap='viridis', square=True, label = f'Potential = {max_pot}') #Normalized potential
    sns.heatmap(P[:,:,i], cmap='viridis', square=True, label = f'Wavefunction') 
    plt.title('Heatmap of Matrix')
    plt.xlabel('X axis')
    plt.ylabel('Y axis')
    plt.legend()
    plt.show()
