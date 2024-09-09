import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(filename_list):
	fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
	for i in range(len(filename_list)):
		h, approx, exact = np.loadtxt(filename_list[i], usecols=(0, 1, 2), unpack=True, skiprows=1)
		h, approx, exact = h[1:], approx[1:], exact[1:]

		absolute_error = np.absolute(approx - exact)
		relative_error = np.absolute(absolute_error / exact)
	
		log10_abs = np.log10(absolute_error)
		log10_rel = np.log10(relative_error)
		log10_h = np.log10(h)


		ax1.plot(h, log10_abs)
		ax1.set_xlabel("h")
		ax1.set_ylabel('error')
		ax1.set_title(f'Absolute')
		ax1.legend()
		ax1.grid(True)

		ax2.plot(h, log10_rel)
		ax2.set_xlabel("h")
		ax2.set_ylabel('error')
		ax2.set_title(f'Relative')
		ax2.legend()
		ax2.grid(True)

	plt.show()

filename_list = ["h-approx-exact10.txt", "h-approx-exact100.txt", "h-approx-exact1000.txt"]
plot_problem8(filename_list)


