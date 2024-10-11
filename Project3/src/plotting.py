import numpy as np
import matplotlib.pyplot as plt

time, z_pos = np.loadtxt("simulation_data_1_particle.txt", unpack=True)

plt.plot(time, z_pos, label = "z - position over 50 microseconds", color = "magenta")
plt.title("movement of a single particle in Penning trap using RK4")
plt.xlabel("time in microseconds")
plt.ylabel("z-values")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()
