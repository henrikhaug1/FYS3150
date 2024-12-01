import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the matrix from the CSV file
filename = 'matrix.csv'
data = pd.read_csv(filename, header=None)

# Create the heatmap
plt.figure(figsize=(10, 10))
sns.heatmap(data, cmap='viridis', square=True)
plt.title('Heatmap of Matrix')
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.show()
