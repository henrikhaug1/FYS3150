import numpy as np
import matplotlib.pyplot as plt

def plot_problem8(path_absolute, path_relative, n_step):
	absolute_error_values = np.zeros(n_step)
	relative_error_values = np.zeros(n_step)
	xi_values = np.linspace(0, 1, n_step)


	with open(path_absolute, "r") as infile:
		absolute_error_list = []
		for line in infile:
			absolute_error_list.append(line.split()[0])
			

		for i in range(0, n_step):
			absolute_error_values[i] = float(absolute_error_list[i])
			

	with open(path_relative, "r") as infile:
		relative_error_list = []
		for line in infile:
			relative_error_list.append(line.split()[0])
		for i in range(0, n_step):
			relative_error_values[i] = float(relative_error_list[i])

	plt.figure(figsize=(12, 8))
	plt.loglog(absolute_error_values, xi_values, 'o-', label='absolute_error_values')
	plt.loglog(relative_error_values, xi_values, 'x--', label='Relative_error_values')

	plt.xlabel('xi-values')
	plt.ylabel('log_10(errors)')
	plt.title(f'plot of log_10(errors) against x_i with n_steps = {n_step}')
	plt.legend()
	plt.grid(True)
	plt.show()
	"""plt.savefig(f"plot_problem7_with_{n_step}_steps.pdf")"""


plot_problem8("/Users/henrikhaug/Documents/Matematikk_med_informatikk/Semester5/FYS3150/Prosjekter_livelst/FYS3150/Project1/absolute_error10.txt", "/Users/henrikhaug/Documents/Matematikk_med_informatikk/Semester5/FYS3150/Prosjekter_livelst/FYS3150/Project1/relative_error10.txt", 10)