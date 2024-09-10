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

fig, ax = plt.subplots(2)
ax[0].plot(x_10, log10_abs_error_10, '--', label="n_step=10", alpha=0.5)
ax[0].plot(x_100, log10_abs_error_100, '--', label="n_step=100", alpha=0.5)
ax[0].plot(x_1000, log10_abs_error_1000, '--', label="n_step=1000", alpha=0.5)
ax[0].set_xlabel("x")
ax[0].set_ylabel("log10(absolute error)")
ax[0].legend()


ax[1].plot(x_10, log10_rel_error_10, '--', label="n_step=10", alpha=0.5)
ax[1].plot(x_100, log10_rel_error_100, '--', label="n_step=100", alpha=0.5)
ax[1].plot(x_1000, log10_rel_error_1000, '--', label="n_step=1000", alpha=0.5)
ax[1].set_xlabel("x")
ax[1].set_ylabel("log10(relative error)")
ax[1].legend()

fig.savefig("x_log_error_plot.pdf")










"""import numpy as np
import matplotlib.pyplot as plt

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 5))

max_epsilon_arr = []
n_step_list = [10, 100, 1000]

# a) Making a plot of log10(absolute_error) with different graphs for different n_step
# --------- n_step = 10 --------
filename_10 = "h-approx-exact10.txt"
h_10, approx_10, exact_10 = np.loadtxt(filename_10, usecols=(0, 1, 2), unpack=True, skiprows=1)
print(approx_10)
h_10, approx_10, exact_10 = h_10[1:], approx_10[1:], exact_10[1:]

absolute_error_10 = np.absolute(approx_10 - exact_10)
relative_error_10 = np.absolute(absolute_error_10 / exact_10)

# Finding maximum relative error
max_epsilon_10 = np.max(relative_error_10)

# Replace zero values with nan to avoid log10(0) which is undefined
absolute_error_10 = np.where(absolute_error_10 == 0, np.nan, absolute_error_10)
relative_error_10 = np.where(relative_error_10 == 0, np.nan, relative_error_10)

log10_abs_error_10 = np.log10(absolute_error_10)
log10_rel_error_10 = np.log10(relative_error_10)

ax1.plot(h_10, log10_abs_error_10, '--', label="n_step=10", alpha=0.5)
ax2.plot(h_10, log10_rel_error_10, '--', label="n_step=10", alpha=0.5)



# --------- n_step = 100 --------
filename_100 = "h-approx-exact100.txt"
h, approx, exact = np.loadtxt(filename_100, usecols=(0, 1, 2), unpack=True, skiprows=1)
h, approx, exact = h[1:], approx[1:], exact[1:]

absolute_error_100 = np.absolute(approx - exact)
relative_error_100 = np.absolute(absolute_error_100 / exact)

# Finding maximum relative error
max_epsilon_100 = np.max(relative_error_100)

# Replace zero values with nan to avoid log10(0) which is undefined
absolute_error_100 = np.where(absolute_error_100 == 0, np.nan, absolute_error_100)
relative_error_100 = np.where(relative_error_100 == 0, np.nan, relative_error_100)

log10_abs_error_100 = np.log10(absolute_error_100)
log10_rel_error_100 = np.log10(relative_error_100)

ax1.plot(h, log10_abs_error_100, label="n_step=100")
ax2.plot(h, log10_rel_error_100, label="n_step=100")


# --------- n_step = 1000 --------
filename_1000= "h-approx-exact1000.txt"
h, approx, exact = np.loadtxt(filename_1000, usecols=(0, 1, 2), unpack=True, skiprows=1)
h, approx, exact = h[1:], approx[1:], exact[1:]

absolute_error_1000 = np.absolute(approx - exact)
relative_error_1000 = np.absolute(absolute_error_1000 / exact)

# Finding maximum relative error
max_epsilon_1000 = np.max(relative_error_1000)

# Replace zero values with nan to avoid log10(0) which is undefined
absolute_error_1000 = np.where(absolute_error_1000 == 0, np.nan, absolute_error_1000)
relative_error_1000 = np.where(relative_error_1000 == 0, np.nan, relative_error_1000)

log10_abs_error_1000 = np.log10(absolute_error_1000)
log10_rel_error_1000 = np.log10(relative_error_1000)

ax1.plot(h, log10_abs_error_1000, '--', label="n_step=1000", alpha=0.5)
ax2.plot(h, log10_rel_error_1000, '--', label="n_step=1000", alpha=0.5)


ax1.set_title("Log10(absolute_error) for x=0.5", fontsize="xx-large")
ax1.set_ylabel("log10(absolute_error)")
ax1.set_xlabel("h")
ax1.legend(loc="lower right", fontsize="large")
#fig.savefig("log10_absolute_error_h.pdf")

ax2.set_title("Log10(relative_error for x=0.5", fontsize="xx-large")
ax2.set_ylabel("log10(relative_error)")
ax2.set_xlabel("h")
ax2.legend(loc="lower right", fontsize="large")
#fig.savefig("log10_relative_error_h.pdf")
plt.show()



# c) Tabel for maximum relative error 
filename = "max_epsilon.txt"

with open(filename, "w") as outfile:
	outfile.write("n_step    max(epsilon)\n")
	for i in range(len(n_step_list)):
		outfile.write(f"{n_step_list[i]:<10}{max_epsilon_arr[i]:>10}\n")



"""