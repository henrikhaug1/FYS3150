import numpy as np
import matplotlib.pyplot as plt

filename_10 = "x_v_u10.txt"
filename_100 = "x_v_u100.txt"
filename_1000 = "x_v_u1000.txt"

x_10, v_10, u_10 = np.loadtxt(filename_10, usecols=(0, 1, 2), unpack=True, skiprows=1)
x_100, v_100, u_100 = np.loadtxt(filename_100, usecols=(0, 1, 2), unpack=True, skiprows=1)
x_1000, v_1000, u_1000 = np.loadtxt(filename_1000, usecols=(0, 1, 2), unpack=True, skiprows=1)

absolute_error_10 = np.absolute(v_10 - u_10)
relative_error_10 = np.absolute(absolute_error_10 / u_10)

absolute_error_100 = np.absolute(v_100 - u_100)
relative_error_100 = np.absolute(absolute_error_100 / u_100)

absolute_error_1000 = np.absolute(v_1000 - u_1000)
relative_error_1000 = np.absolute(absolute_error_1000 / u_1000)


log10_abs_error_10 = np.log10(absolute_error_10)
log10_rel_error_10 = np.log10(relative_error_10)

log10_abs_error_100 = np.log10(absolute_error_100)
log10_rel_error_100 = np.log10(relative_error_100)

log10_abs_error_1000 = np.log10(absolute_error_1000)
log10_rel_error_1000 = np.log10(relative_error_1000)

fig1, ax1 = plt.subplots(2)
ax1[0].plot(x_10, log10_abs_error_10, '--', label="n_step=10", alpha=0.5)
ax1[0].plot(x_100, log10_abs_error_100, '--', label="n_step=100", alpha=0.5)
ax1[0].plot(x_1000, log10_abs_error_1000, '--', label="n_step=1000", alpha=0.5)
ax1[0].set_xlabel("x")
ax1[0].set_ylabel("log10(absolute error)")
ax1[0].legend()


ax1[1].plot(x_10, log10_rel_error_10, '--', label="n_step=10", alpha=0.5)
ax1[1].plot(x_100, log10_rel_error_100, '--', label="n_step=100", alpha=0.5)
ax1[1].plot(x_1000, log10_rel_error_1000, '--', label="n_step=1000", alpha=0.5)
ax1[1].set_xlabel("x")
ax1[1].set_ylabel("log10(relative error)")
ax1[1].legend()

fig1.savefig("x_log_error_plot.pdf")







