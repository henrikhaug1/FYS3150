import numpy as np
import matplotlib.pyplot as plt

#---------------------------------------
h, approx, exact = np.loadtxt("output.txt", usecols = (0, 1, 2), unpack = True)
abs_err = abs(approx - exact)
rel_err = abs((approx - exact) / exact)
log10_rel_err = np.log10(rel_err)
log10_h = np.log10(h)

exact_result = exact[0]
common_title_string = "for approximation of\n u''(x=2) = 4*exp(2*2) = {:.8e}".format(exact_result)

figwidth = 5.5
figheight = figwidth / 1.33333

# Plot absolute error vs h
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("h")
plt.savefig("abs_err_vs_h.pdf")

# Plot absolute error vs log10(h)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("log10(h)")
plt.savefig("abs_err_vs_log10_h.pdf")

<<<<<<< HEAD
# Plot absolute error vs h on log-log axes
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("h")
plt.xscale("log")
plt.yscale("log")
plt.savefig("abs_err_vs_h_loglog.pdf")
=======
			plt.plot(np.log10(error_values, xi_values), label = f"error_values_{n_step_list[i]}")
>>>>>>> c3127ce (umm??)

# Plot relative error vs log10(h)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, rel_err, '.', c="black", markersize=10)
plt.title("Relative error " + common_title_string, fontsize=10)
plt.ylabel("relative error")
plt.xlabel("log10(h)")
plt.savefig("rel_err_vs_log10_h.pdf")

# Plot log10(relative error) vs log10(h)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, log10_rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, log10_rel_err, '.', c="black", markersize=10)
plt.title("Log10(relative error) " + common_title_string, fontsize=10)
plt.ylabel("log10(relative error)")
plt.xlabel("log10(h)")
plt.savefig("log10_rel_err_vs_log10_h.pdf")

# Plot relative error vs h on log-log axes
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, rel_err, '.', c="black", markersize=10)
plt.title("Relative error " + common_title_string, fontsize=10)
plt.ylabel("relative error")
plt.xlabel("h")
plt.xscale("log")
plt.yscale("log")
plt.savefig("rel_err_vs_h_loglog.pdf")

<<<<<<< HEAD
n_step_list_relative = [10, 100, 1000]
error_type_relative = "relative"
plot_problem8(error_type_relative, n_step_list_relative)
=======
>>>>>>> a34d7e5 (updated problem8_functions.cpp and continued on main and python file)
