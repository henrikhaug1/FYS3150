import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

potential_file = 'Potential.csv'
P_file = 'P.csv'
U_real_file = 'U_Real.csv'
U_imag_file = 'U_imag.csv'
prob_file = 'Prob_vec.csv'

pot_data = pd.read_csv(potential_file, header=None)
max_pot = np.max(pot_data)
P = pd.read_csv(P_file, header = None)                # P is 2D representing 3D
U_real = pd.read_csv(U_real_file, header = None)     
U_imag = pd.read_csv(U_imag_file, header = None)      
prob = pd.read_csv(prob_file, header = None)

P = P.values
U_real = U_real.values
U_imag = U_imag.values
prob = prob.values[0]

rows, cols = P.shape
M_2 = int(np.sqrt(rows))
timesteps = cols

# Reshape the 2D array into a 3D array
P = P.reshape((M_2, M_2, timesteps)) 
U_real = U_real.reshape((M_2, M_2, timesteps)) 
U_imag = U_imag.reshape((M_2, M_2, timesteps)) 

num_labels = 6  
x_ticks = np.linspace(0, M_2, num_labels)  
x_labels = np.linspace(0, 1, num_labels) 
y_labels = np.linspace(1, 0, num_labels) #The y-axis' are inverted

def plot_probabilities():
    time = np.linspace(0, 0.002, timesteps)
    prob_log = np.log(prob)
    plt.plot(time, prob_log)
    plt.xlabel('time', fontsize = 16)
    plt.ylabel('log(probability)', fontsize = 16)
    plt.xticks(fontsize = 16)
    plt.yticks(fontsize = 16)
    plt.show()
plot_probabilities()

def plot_potential():
    plt.figure(figsize=(10, 10))
    sns.heatmap(pot_data, cmap='viridis', square=True, xticklabels=x_ticks, yticklabels=x_ticks)
    # plt.title('The double slit', fontsize = 18)
    plt.xticks(x_ticks, [f"{label:.1f}" for label in x_labels], fontsize = 16)  
    plt.yticks(x_ticks, [f"{label:.1f}" for label in y_labels], fontsize = 16) 
    plt.xlabel('X axis', fontsize = 16)
    plt.ylabel('Y axis', fontsize = 16)
    plt.legend()
    plt.show()
plot_potential()

def plot_three_times(data):
    'data is either P, U_real, or U_imag'
    t_3_id = [0, int(timesteps / 2), timesteps - 1]
    for i in t_3_id:
        plt.figure(figsize=(10, 10))
        # sns.heatmap(pot_data / (max_pot), cmap='viridis', square=True, label = f'Potential = {max_pot}') #Normalized potential. doesn't quite work
        sns.heatmap(data[:,:,i], cmap='viridis', square=True) 
        # plt.title('Probability of finding the particle', fontsize = 18)
        plt.xlabel('X axis', fontsize = 16)
        plt.ylabel('Y axis', fontsize = 16)
        plt.xticks(x_ticks, [f"{label:.1f}" for label in x_labels], fontsize = 16)  
        plt.yticks(x_ticks, [f"{label:.1f}" for label in y_labels], fontsize = 16) 
        plt.show()
plot_three_times(P)
