import numpy as np
import matplotlib.pyplot as plt

# ---------- Plotting z-position ----------
time_z, z_pos = np.loadtxt("specific_analytical_z.txt", unpack=True, skiprows=1)

# Create a figure for the z-position plot
plt.figure(figsize=(10, 6))
plt.plot(time_z, z_pos, label="z - position over 50 microseconds", color="magenta")
plt.title("Movement of a Single Particle in Penning Trap")
plt.xlabel("Time (microseconds)")
plt.ylabel("z(t)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()

# ---------- Plotting x vs y in subplots ----------
x1, y1 = np.loadtxt("specific_analytical_xy_particle1.txt", unpack=True, skiprows=1)
x2, y2 = np.loadtxt("specific_analytical_xy_particle1_interactions.txt", unpack=True, skiprows=1)

fig, axs = plt.subplots(2, 1, figsize=(10, 12))


axs[0].plot(x1, y1, label="x vs y without interaction", color="blue")
axs[0].set_title("Trajectory of Particle 1 in x-y Plane (No Interaction)")
axs[0].set_xlabel("x Position")
axs[0].set_ylabel("y Position")
axs[0].grid(True)
axs[0].legend()

axs[1].plot(x2, y2, label="x vs y with interaction", color="pink")
axs[1].set_title("Trajectory of Particle 1 in x-y Plane (With Interaction)")
axs[1].set_xlabel("x Position")
axs[1].set_ylabel("y Position")
axs[1].grid(True)
axs[1].legend()

plt.tight_layout()
plt.show()
