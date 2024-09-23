import matplotlib.pyplot as plt
import numpy as np

# Load numerical and analytical eigenvectors
numerical_eigvecs = np.loadtxt("numerical_smallest_lambda.txt", usecols=(0, 1, 2), skiprows=1)
analytical_eigvecs = np.loadtxt("analytical_smallest_lambda.txt", usecols=(0, 1, 2), skiprows=1)

# Assuming x-coordinates are uniformly spaced between 0 and 1
N = numerical_eigvecs.shape[0]
x_hat = np.linspace(0, 1, N)

# Plotting
fig, ax = plt.subplots(3, figsize=(10, 8))

# Plot each eigenvector
for i in range(3):
	#setting boundary points
	numerical_eigvecs[0, i] = 0
	numerical_eigvecs[-1, i] = 0
	analytical_eigvecs[0, i] = 0
	analytical_eigvecs[-1, i] = 0


	ax[i].plot(x_hat, numerical_eigvecs[:, i], label=f"Numerical Eigenvector {i+1}", color='magenta')
	ax[i].plot(x_hat, analytical_eigvecs[:, i], label=f"Analytical Eigenvector {i+1}", linestyle = "--", color='blue')
	ax[i].set_xlabel("x_hat")
	ax[i].set_ylabel("Value")
	ax[i].set_title(f"Eigenvector Comparison {i+1}")
	ax[i].legend()
	ax[i].grid()

plt.tight_layout()
plt.show()
