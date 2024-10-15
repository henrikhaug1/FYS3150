import numpy as np
import matplotlib.pyplot as plt

time_z, z_pos = np.loadtxt("specific_analytical_z.txt", unpack=True)

# Plot z-position
time_z, z_pos = np.loadtxt("specific_analytical_z.txt", unpack=True)
plt.plot(time_z, z_pos, label="z - position over 50 microseconds", color="magenta")
plt.title("Movement of a Single Particle in Penning Trap")
plt.xlabel("Time in Microseconds")
plt.ylabel("z(t)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()


x1, y1 = np.loadtxt("specific_analytical_xy_particle1.txt", unpack=True)

# Plot x vs y
plt.plot(x1, y1, label="Motion of Particle 1 in xy-Plane", color="blue")
plt.title("Trajectory of Particle 1 in x-y Plane")
plt.xlabel("x Position")
plt.ylabel("y Position")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()
