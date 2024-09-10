"""import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(filename_list):
	fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(5.5, 5.5/1.333))
	for i in range(len(filename_list)):
		h, approx, exact = np.loadtxt(filename_list[i], usecols=(0, 1, 2), unpack=True, skiprows=1)
		h, approx, exact = h[1:], approx[1:], exact[1:]

		absolute_error = np.absolute(approx - exact)
		relative_error = np.absolute(absolute_error / exact)
	
		log10_abs = np.log10(absolute_error)
		log10_rel = np.log10(relative_error)
		log10_h = np.log10(h)

		ax1.plot(log10_h, log10_abs)
		ax1.set_xlabel("h")
		ax1.set_ylabel('error')
		ax1.set_title(f'Absolute')
		ax1.legend()

		ax1.grid(True)

		ax2.plot(log10_h, log10_rel)

		ax2.set_ylabel('error')
		ax2.set_title(f'Relative')
		ax2.legend()
		ax2.grid(True)


	plt.show()

filename_list = ["h-approx-exact10.txt", "h-approx-exact100.txt", "h-approx-exact1000.txt"]
plot_problem8(filename_list)
"""

import numpy as np
import matplotlib.pyplot as plt

filename = "h-approx-exact10.txt"
h, approx, exact = np.loadtxt(filename, usecols=(0, 1, 2), unpack=True, skiprows=1)
h, approx, exact = h[1:], approx[1:], exact[1:]

abs_err = np.absolute(approx - exact)
rel_err = np.absolute(abs_err / exact)

log10_abs_err = np.log10(abs_err)
log10_rel_err = np.log10(rel_err)
log10_h = np.log10(h)

figwidth = 5.5
figheight = figwidth / 1.33333
common_title_string = "moren din"




plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, log10_rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, log10_rel_err, '.', c="black", markersize=10)
plt.title("Log10(relative error) " + common_title_string, fontsize=10)
plt.ylabel("log10(relative error)")
plt.xlabel("log10(h)")
plt.savefig("log10_rel_err_vs_h.pdf")

plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, log10_abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, log10_abs_err, '.', c="black", markersize=10)
plt.title("Log10(relative error) " + common_title_string, fontsize=10)
plt.ylabel("log10(relative error)")
plt.xlabel("log10(h)")
plt.savefig("log10_rel_err_vs_log10_h.pdf")



"""
# Plot absolute error vs h
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("h")
plt.savefig("abs_err_vs_h.pdf")"""

"""# Plot absolute error vs log10(h)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("log10(h)")
plt.savefig("abs_err_vs_log10_h.pdf")"""

"""# Plot absolute error vs h on log-log axes
plt.figure(figsize=(figwidth, figheight))
plt.plot(h, abs_err, '--', c="0.8", linewidth=1.5)
plt.plot(h, abs_err, '.', c="black", markersize=10)
plt.title("Absolute error " + common_title_string, fontsize=10)
plt.ylabel("absolute error")
plt.xlabel("h")
plt.xscale("log")
plt.yscale("log")
plt.savefig("abs_err_vs_h_loglog.pdf")
"""
"""# Plot relative error vs log10(h)
plt.figure(figsize=(figwidth, figheight))
plt.plot(log10_h, rel_err, '--', c="0.8", linewidth=1.5)
plt.plot(log10_h, rel_err, '.', c="black", markersize=10)
plt.title("Relative error " + common_title_string, fontsize=10)
plt.ylabel("relative error")
plt.xlabel("log10(h)")
plt.savefig("rel_err_vs_log10_h.pdf")"""

"""# Plot log10(relative error) vs log10(h)
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
plt.savefig("rel_err_vs_h_loglog.pdf")"""