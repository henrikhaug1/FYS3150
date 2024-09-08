import numpy as np
import matplotlib.pyplot as plt

def u(x):
	func = (1 - ((1 - np.exp(-10)) * x) - np.exp(-10 * x))
	return func

def plot_problem7(filename_list, n_step_list):
	plt.figure(figsize=(12, 8))


	for i in range(len(n_step_list)):
		v_values = np.zeros(n_step_list[i])
		x_values = np.zeros(n_step_list[i])
		ux_values = np.zeros(n_step_list[i])


		with open(filename_list[i], "r") as infile:
			v_list = []
			x_list = []
			for _ in range(7):
				infile.readline()
			for line in infile:
				v_list.append(line.split()[0])
				x_list.append(line.split()[1])

			for j in range(n_step_list[i]):
				v_values[j] = float(v_list[j])
				x_values[j] = float(x_list[j])
				ux_values[j] = u(x_values[j])

			plt.plot(x_values, v_values, "--", label=f"{n_step_list[i]} approx")

			if i == len(n_step_list) - 1: #only ploting exact solution for n_step = 1000
				plt.plot(x_values, ux_values, label="exact")




	plt.xlabel('')
	plt.ylabel('x_values')
	plt.title(f'Comparison of Numerical Solution and Exact Solution with different n_step')
	plt.legend()
	plt.grid(True)
	plt.show()

filename_list = ["problem7_v_x_10steps.txt", "problem7_v_x_100steps.txt", "problem7_v_x_1000steps.txt"]
n_step_list = [10, 100, 1000]
plot_problem7(filename_list, n_step_list)



