import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

potential_file = 'Potential.csv'
P_file = 'P.csv'

pot_data = pd.read_csv(potential_file, header=None)
max_pot = np.max(pot_data)
P = pd.read_csv(P_file, header = None)

print(P)

for i in range(2):
    plt.figure(figsize=(10, 10))
    sns.heatmap(pot_data / max_pot, cmap='viridis', square=True, label = f'Potential = {max_pot}') #Normalized potential
    sns.heatmap(P, cmap='viridis', square=True, label = f'Wavefunction') #Normalized potential
    plt.title('Heatmap of Matrix')
    plt.xlabel('X axis')
    plt.ylabel('Y axis')
    plt.legend()
    plt.show()
