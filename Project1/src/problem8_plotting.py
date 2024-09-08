import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(type_error, filename_list):

	for i in range(len(filename_list)):
		h_values = []
		absolute_values = []
		relative_values = []
		with open(filename_list[i], "r") as infile:
			infile.readline()
			for line in infile:
				h_values.append(float(line.split()[0]))
				absolute_values.append(float(line.split()[1]))
				relative_values.append(float(line.split()[2]))

		if type_error == "absolute":
			plt.plot(h_values, np.log10(absolute_values))

		elif type_error == "relative":
			plt.plot(h_values, np.log10(relative_values))
		else:
			print("type_error has to be relative or absolute")


		
		

	plt.show()

filename_list = ["h-abs-rel10.txt", "h-abs-rel100.txt", "h-abs-rel1000.txt"]
plot_problem8("absolute", filename_list)