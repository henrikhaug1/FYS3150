import numpy as np
import matplotlib.pyplot as plt

time_z, z_pos = np.loadtxt("specific_analytical_z.txt", unpack=True)


plt.plot(time_z, z_pos, label = "z - position over 50 microseconds", color = "magenta")
plt.title("movement of a single particle in Penning trap using RK4")
plt.xlabel("time in microseconds")
plt.ylabel("z(t)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()

x1, y1 = np.loadtxt("specific_analytical_xy_particle1.txt", unpack=True)



plt.plot(x1, y1, label = "z - position over 50 microseconds", color = "blue")
plt.title("movement of a single particle in Penning trap using RK4")
plt.xlabel("time in microseconds")
plt.ylabel("f(t)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()

x2, y2 = np.loadtxt("specific_analytical_xy_particle2.txt", unpack=True)
plt.plot(x2, y2, label = "z - position over 50 microseconds", color = "red")
plt.title("movement of a single particle in Penning trap using RK4")
plt.xlabel("time in microseconds")
plt.ylabel("f(t)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.show()