import numpy as np
import matplotlib.pyplot as plt

time, z_pos = np.loadtxt("simulation_data_1_particle.txt", unpack=True)

plt.plot(time, z_pos)
plt.show()