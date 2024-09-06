import numpy as np
import matplotlib.pyplot as plt

def u(x):
	func = (1 - ((1 - np.exp(-10)) * x) - np.exp(-10 * x))
	return func

def plot_problem7(path, n_step):
	v_values = np.zeros(n_step)
	x_values = np.zeros(n_step)
	ux_values = np.zeros(n_step)


	with open(path, "r") as infile:
		v_list = []
		x_list = []
		for _ in range(7):
			infile.readline()
		for line in infile:
			v_list.append(line.split()[0])
			x_list.append(line.split()[1])

		for i in range(0, n_step):
			v_values[i] = float(v_list[i])
			x_values[i] = float(x_list[i])
			ux_values[i] = u(x_values[i])


	plt.figure(figsize=(12, 8))
	plt.plot(x_values, v_values, 'o-', label='Numerical v-values')
	plt.plot(x_values, ux_values, 'x--', label='Exact u(x)')

	plt.xlabel('x-values')
	plt.ylabel('Values')
	plt.title('Comparison of Numerical Solution and Exact Solution')
	plt.legend()
	plt.grid(True)
	plt.savefig(f"plot_problem7_with_{n_step}_steps")

plot_problem7("/Users/henrikhaug/Documents/Matematikk_med_informatikk/Semester5/FYS3150/Prosjekter_livelst/FYS3150/Project1/problem7_v_x_10steps.txt", 10)
plot_problem7("/Users/henrikhaug/Documents/Matematikk_med_informatikk/Semester5/FYS3150/Prosjekter_livelst/FYS3150/Project1/problem7_v_x_100steps.txt", 100)
plot_problem7("/Users/henrikhaug/Documents/Matematikk_med_informatikk/Semester5/FYS3150/Prosjekter_livelst/FYS3150/Project1/problem7_v_x_1000steps.txt", 1000)



