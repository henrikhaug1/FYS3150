import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(error_type, n_step_list):

	plot = plt.figure(figsize=(12, 8))

	for i in range(len(n_step_list)):
		with open("../" + str(error_type) + f"_error{n_step_list[i]}.txt", "r") as infile:

			error_values = np.zeros(n_step_list[i])
			xi_values = np.linspace(0, 1, n_step_list[i])

			error_list = []
			for line in infile:
				error_list.append(line.split()[0])
			for j in range(0, n_step_list[i]):
				error_values[j] = float(error_list[j])

			plt.loglog(error_values, xi_values, label = f"error_values_{n_step_list[i]}")


	plt.xlabel('xi-values')
	plt.ylabel('log_10(errors)')
	plt.title(f'plot of log_10(errors) against x_i with n_steps = {n_step_list[i]}')
	plt.legend()
	plt.grid(True)
	plt.show()

n_step_list_absolute = [10, 100, 1000]
error_type_absolute = "absolute"
plot_problem8(error_type_absolute, n_step_list_absolute)

n_step_list_relative = [10, 100, 1000]
error_type_relative = "relative"
plot_problem8(error_type_relative, n_step_list_relative)