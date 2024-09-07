import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(filename, n_step_list):
	for i in n_step_list:	
		h_values = np.zeros(n_step_list[i])
		absolute_values = np.zeros(n_step_list[i])
		relative_values = np.zeros(n_step_list[i])
		with open(filename, "r") as infile:
			for line in infile():
				infile.readline()
			h_list = []
			abs_list = []
			rel_list = []

			for line in infile:
				h_list.append(line.split[0])
				abs_list.append(line.split[1])
				rel_list.append(line.split[2])

			for j in range(n_step_list[i]):
				h_values[j] = h_list[j]
				absolute_values[j] = abs_list[j]
				relative_values[j] = rel_list[j]

		plt.plot(np.log10(absolute_values), h_values)
		plt.plot(np.log10(relative_values), h_values)
	plt.show()