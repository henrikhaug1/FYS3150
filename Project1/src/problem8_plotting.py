import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(type_error, filename_list):
	plt.figure(figsize=(12, 8))

	for i in range(len(filename_list)):
		h_values = []
		absolute_values = []
		relative_values = []
		steps = 0
		with open(filename_list[i], "r") as infile:
			infile.readline()
			for line in infile:
				steps +=1
				h_values.append(float(line.split()[0]))
				absolute_values.append(float(line.split()[1]))
				relative_values.append(float(line.split()[2]))

		if type_error == "absolute":
			plt.plot(h_values, np.log10(absolute_values), label=f"absolute error with {steps} amounts of steps")

		elif type_error == "relative":
			plt.plot(h_values, np.log10(relative_values), label=f"relative eerror with {steps} amounts of steps")
		else:
			print("type_error has to be relative or absolute")

	plt.xlabel("step")
	plt.ylabel('error')
	plt.title(f'Comparison of {type_error} for different amounts of n steps')
	plt.legend()
	plt.grid(True)
	plt.show()

filename_list = ["h-approx-exact10.txt", "h-approx-exact100.txt", "h-approx-exact1000.txt"]
plot_problem8("absolute", filename_list)

