import numpy as np
import matplotlib.pyplot as plt


# ---------- Reading variables ----------
time_analytical, x_analytical, y_analytical, z_analytical = np.loadtxt("xyz_analytical.txt", unpack=True, skiprows=1)











# ---------- Plotting - Specific analytical solution z(t) ----------

plt.plot(x_analytical, y_analytical)
plt.show()

"""
axs[0].plot(x1, y1, label="Particle trajectory", color="blue")
axs[0].set_title("Specific analytical solution of particle 1 in xy-plane")
axs[0].set_xlabel("x Position")
axs[0].set_ylabel("y Position")
axs[0].grid(True)
axs[0].legend()
"""

# ---------- Plotting - Specific analytical solution (x, y)-plane  ------------





"""

# ---------- Plotting - Specific analytical solution (x, y)-plane  ------------

x2, y2 = np.loadtxt("specific_analytical_xy_particle2.txt", unpack=True, skiprows=1)

fig, axs = plt.subplots(2, 1, figsize=(10, 12))

axs[0].plot(x2, y2, label="Particle trajectory", color="blue")
axs[0].set_title("Specific analytical solution of particle 2 in xy-plane")
axs[0].set_xlabel("x Position")
axs[0].set_ylabel("y Position")
axs[0].grid(True)
axs[0].legend()

time_z_2, z_pos_2 = np.loadtxt("specific_analytical_z.txt", unpack=True, skiprows=1)

# Create a figure for the z-position plot
axs[1].plot(time_z_2, z_pos_2, label="z - position over 50 microseconds", color="magenta")
axs[1].set_title("Specific analytical solution of particle 2 in z-direction")
axs[1].set_xlabel("Time (microseconds)")
axs[1].set_ylabel("z(t)")
axs[1].grid(True)
axs[1].legend()

plt.tight_layout()
plt.savefig('Specific_particle2.png')
plt.show()

# ---------- Plotting RK4 ----------

# ---------- Plotting FWD Euler ----------

# ---------- Plotting relative error ----------
"""