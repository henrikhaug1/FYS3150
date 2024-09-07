import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(filename):

	for i in n_step_list:	

		h_values = []
		absolute_values = []
		relative_values = []
		with open(filename, "r") as infile:
			for line in infile():
				infile.readline()

				h_values.append(line.split[0])
				absolute_values.append(line.split[1])
				relative_values.append(line.split[2])

		plt.plot(h_values, np.log10(absolute_values))
		plt.plot(h_values, np.log10(relative_values))
	plt.show()

plot_problem8("h-abs-rel.txt")