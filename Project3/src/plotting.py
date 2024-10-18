import numpy as np
import matplotlib.pyplot as plt


# ---------- Reading variables ----------
time_analytical, x_analytical, y_analytical, z_analytical = np.loadtxt("xyz_analytical.txt", unpack=True, skiprows=1)

time_RK4_1, x_RK4_1, y_RK4_1, z_RK4_1 = np.loadtxt("xyz_RK4_1.txt", unpack=True, skiprows=1)
time_RK4_1_velocity, x_RK4_1_velocity, y_RK4_1_velocity, z_RK4_1_velocity = np.loadtxt("xyz_RK4_1.txt", unpack=True, skiprows=1)

time_RK4_2, x_RK4_2, y_RK4_2, z_RK4_2 = np.loadtxt("xyz_RK4_2.txt", unpack=True, skiprows=1)
time_RK4_2_velocity, x_RK4_2_velocity, y_RK4_2_velocity, z_RK4_2_velocity = np.loadtxt("xyz_RK4_2.txt", unpack=True, skiprows=1)

time_RK4_interactions_1, x_RK4_interactions_1, y_RK4_interactions_1, z_RK4_interactions_1 = np.loadtxt("xyz_RK4_interactions_1.txt", unpack=True, skiprows=1)
time_RK4_interactions_1_velocity, x_RK4_interactions_1_velocity, y_RK4_interactions_1_velocity, z_RK4_interactions_1_velocity = np.loadtxt("xyz_RK4_interactions_1.txt", unpack=True, skiprows=1)

time_RK4_interactions_2, x_RK4_interactions_2, y_RK4_interactions_2, z_RK4_interactions_2 = np.loadtxt("xyz_RK4_interactions_2.txt", unpack=True, skiprows=1)
time_RK4_interactions_2_velocity, x_RK4_interactions_2_velocity, y_RK4_interactions_2_velocity, z_RK4_interactions_2_velocity = np.loadtxt("xyz_RK4_interactions_2.txt", unpack=True, skiprows=1)

time_FE, x_FE, y_FE, z_FE = np.loadtxt("xyz_FE.txt", unpack=True, skiprows=1)





# ---------- Plotting - z(t) ----------
plt.figure(figsize=(10, 6))
plt.plot(time_RK4_1, z_RK4_1, label="RK4 - motion in z direction", color="blue")
plt.title('Motion in z Direction Over Time')
plt.xlabel('Time')
plt.ylabel('Position (z)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# ---------- Plotting - xy-plane without interactions ----------
plt.figure(figsize=(10, 6))
plt.plot(x_RK4_1, y_RK4_1, label="Particle 1", color="red")
plt.plot(x_RK4_2, y_RK4_2, label="Particle 2", color="blue")
plt.title('XY-Plane Without Interactions')
plt.xlabel('Position (x)')
plt.ylabel('Position (y)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# ---------- Plotting - xy-plane with interactions ----------
plt.figure(figsize=(10, 6))
plt.plot(x_RK4_interactions_1, y_RK4_interactions_1, label="Particle 1", color="red")
plt.plot(x_RK4_interactions_2, y_RK4_interactions_2, label="Particle 2", color="blue")
plt.title('XY-Plane With Interactions')
plt.xlabel('Position (x)')
plt.ylabel('Position (y)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# ---------- Plotting - trajectory phase space plot without interactions (x, v_x) ----------
plt.figure(figsize=(10, 6))
plt.plot(x_RK4_1, x_RK4_1_velocity, label="Particle 1", color="red")
plt.plot(x_RK4_2, x_RK4_2_velocity, label="Particle 2", color="blue")
plt.title('Phase Space Plot (x vs. v_x) Without Interactions')
plt.xlabel('Position (x)')
plt.ylabel('Velocity (v_x)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

#---------- Plotting - trajectory phase space plot with interactions ----------
plt.figure(figsize=(10, 6))
plt.plot(z_RK4_1, z_RK4_1_velocity, label="Particle 1", color="red")
plt.plot(z_RK4_2, z_RK4_2_velocity, label="Particle 2", color="blue")
plt.title('Phase Space Plot (x vs. v_x) Without Interactions')
plt.xlabel('Position (x)')
plt.ylabel('Velocity (v_x)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# ---------- 3D Plotting - Without Interactions ----------
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x_RK4_1, y_RK4_1, z_RK4_1, label="Particle 1", color="red")
ax.plot(x_RK4_2, y_RK4_2, z_RK4_2, label="Particle 2", color="blue")
ax.set_title('3D Trajectories Without Interactions')
ax.set_xlabel('Position (x)')
ax.set_ylabel('Position (y)')
ax.set_zlabel('Position (z)')
ax.legend()
plt.tight_layout()
plt.show()

# ---------- 3D Plotting - With Interactions ----------
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x_RK4_interactions_1, y_RK4_interactions_1, z_RK4_interactions_1, label="Particle 1", color="red")
ax.plot(x_RK4_interactions_2, y_RK4_interactions_2, z_RK4_interactions_2, label="Particle 2", color="blue")
ax.set_title('3D Trajectories With Interactions')
ax.set_xlabel('Position (x)')
ax.set_ylabel('Position (y)')
ax.set_zlabel('Position (z)')
ax.legend()
plt.tight_layout()
plt.show()