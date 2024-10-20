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

time_FE_1, x_FE_1, y_FE_1, z_FE_1 = np.loadtxt("xyz_FE_1.txt", unpack=True, skiprows=1)
time_FE_1_interactions, x_FE_1_interactions, y_FE_1_interactions, z_FE_1_interactions = np.loadtxt("xyz_FE_1_interactions.txt", unpack=True, skiprows=1)

time_FE_2, x_FE_2, y_FE_2, z_FE_2 = np.loadtxt("xyz_FE_2.txt", unpack=True, skiprows=1)
time_FE_2_interactions, x_FE_2_interactions, y_FE_2_interactions, z_FE_2_interactions = np.loadtxt("xyz_FE_2_interactions.txt", unpack=True, skiprows=1)

time_4000, error_RK4_4000 = np.loadtxt('relative_error_RK4_4000.txt', unpack=True, skiprows=1)
time_8000, error_RK4_8000 = np.loadtxt('relative_error_RK4_8000.txt', unpack=True, skiprows=1)
time_16000, error_RK4_16000 = np.loadtxt('relative_error_RK4_16000.txt', unpack=True, skiprows=1)
time_32000, error_RK4_32000 = np.loadtxt('relative_error_RK4_32000.txt', unpack=True, skiprows=1)

time_4000, error_FE_4000 = np.loadtxt('relative_error_FE_4000.txt', unpack=True, skiprows=1)
time_8000, error_FE_8000 = np.loadtxt('relative_error_FE_8000.txt', unpack=True, skiprows=1)
time_16000, error_FE_16000 = np.loadtxt('relative_error_FE_16000.txt', unpack=True, skiprows=1)
time_32000, error_FE_32000 = np.loadtxt('relative_error_FE_32000.txt', unpack=True, skiprows=1)



# ---------- Plotting - z(t) ----------
plt.figure(figsize=(10, 6))
plt.plot(time_RK4_1, z_RK4_1, label="RK4", color="blue", alpha=0.7)
plt.plot(time_FE_1, z_FE_1, label="FE", color="pink", alpha=0.5)
plt.plot(time_analytical, z_analytical, label="Analytical", color="red", alpha=0.5)
plt.xlabel('Time in microseconds', fontsize=16)
plt.ylabel('Position (z)', fontsize=16  )
plt.legend(fontsize=16)
plt.grid(True)
plt.tight_layout()
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.savefig("8.1_z_t.pdf")
plt.show()

# ---------- Plotting - xy-plane without interactions ----------
plt.figure(figsize=(10, 6))

plt.plot(x_RK4_1, y_RK4_1, label="Particle 1 (RK4)", color="blue")
plt.plot(x_RK4_2, y_RK4_2, label="Particle 2 (RK4)", color="red")

plt.scatter(x_FE_1, y_FE_1, label="Particle 1 (FE)", color="lightsteelblue")
plt.scatter(x_FE_2, y_FE_2, label="Particle 2 (FE)", color="plum")

plt.xlabel('Position (x)', fontsize=16)
plt.ylabel('Position (y)', fontsize=16)
plt.legend(fontsize=16)
plt.grid(True)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.tight_layout()
plt.savefig("XY-Plane_without_interactions.pdf")
plt.show()

# ---------- Plotting - Single plot of analytical solution of xy-plane for particle 1 ----------

plt.figure(figsize=(10, 6))

plt.plot(x_analytical, y_analytical, label = "Particle 1", color="red")

plt.xlabel('Position (x)', fontsize=16)
plt.ylabel('Position (y)', fontsize=16)
plt.legend(fontsize=16)
plt.grid(True)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.tight_layout()
plt.savefig("XY-Plane_analytical.pdf")
plt.show()

# ---------- Plotting - xy-plane with interactions ----------
plt.figure(figsize=(10, 6))

plt.plot(x_RK4_interactions_1, y_RK4_interactions_1, label="Particle 1 (RK4)", color="red")
plt.plot(x_RK4_interactions_2, y_RK4_interactions_2, label="Particle 2 (RK4)", color="blue")

plt.scatter(x_FE_1_interactions, x_FE_1_interactions, label="Particle 1 (FE)", color="red")
plt.scatter(x_FE_2_interactions, x_FE_2_interactions, label="Particle 2 (FE)", color="blue")


plt.title('XY-Plane With Interactions')
plt.xlabel('Position (x)')
plt.ylabel('Position (y)')
plt.legend(fontsize=16)
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
plt.savefig("")
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


fig, axs = plt.subplots(1, 2, figsize=(12, 6))

# RK4 Plot
axs[0].plot(time_4000, error_RK4_4000, label="RK4, 4000 steps", markersize=1)
axs[0].plot(time_8000, error_RK4_8000, label="RK4, 8000 steps", markersize=1)
axs[0].plot(time_16000, error_RK4_16000, label="RK4, 16000 steps", markersize=1)
axs[0].plot(time_32000, error_RK4_32000, label="RK4, 32000 steps", markersize=1)
axs[0].set_xlabel("Time (microseconds)")
axs[0].set_ylabel("Relative Error")
axs[0].set_yscale("log")  # Log scale for better readability
axs[0].legend()
axs[0].set_title("Relative Error of RK4 at Different Resolutions")

# FE Plot
axs[1].plot(time_4000, error_FE_4000, label="FE, 4000 steps")
axs[1].plot(time_8000, error_FE_8000, label="FE, 8000 steps")
axs[1].plot(time_16000, error_FE_16000, label="FE, 16000 steps")
axs[1].plot(time_32000, error_FE_32000, label="FE, 32000 steps")
axs[1].set_xlabel("Time (microseconds)")
axs[1].set_yscale("log")  # Log scale for better readability
axs[1].legend()
axs[1].set_title("Relative Error of FE at Different Resolutions")

plt.tight_layout()
plt.show()



