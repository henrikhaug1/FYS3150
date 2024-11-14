import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

t1_ordered_i, t1_ordered_e, t1_ordered_cum_e, t1_ordered_mag = np.loadtxt("energy_L20_T1.000000_ordered.txt", unpack=True)
t1_unordered_i, t1_unordered_e, t1_unordered_cum_e, t1_unordered_mag = np.loadtxt("energy_L20_T1.000000_unordered.txt", unpack=True)
t2_4_ordered_i, t2_4_ordered_e, t2_4_ordered_cum_e, t2_4_ordered_mag = np.loadtxt("energy_L20_T2.400000_ordered.txt", unpack=True)
t2_4_unordered_i, t2_4_unordered_e, t2_4_unordered_cum_e, t2_4_unordered_mag = np.loadtxt("energy_L20_T2.400000_unordered.txt", unpack=True)

temp2, energy2, magnetization2, heat_cap2, sus2 = np.loadtxt("L2_func_of_temp.txt", unpack=True, skiprows=1)
temp40, energy40, magnetization40, heat_cap40, sus40 = np.loadtxt("L40_func_of_temp.txt", unpack=True, skiprows=1)
temp60, energy60, magnetization60, heat_cap60, sus60 = np.loadtxt("L60_func_of_temp.txt", unpack=True, skiprows=1)
temp80, energy80, magnetization80, heat_cap80, sus80 = np.loadtxt("L80_func_of_temp.txt", unpack=True, skiprows=1)
temp100, energy100, magnetization100, heat_cap100, sus100 = np.loadtxt("L100_func_of_temp.txt", unpack=True, skiprows=1)




plt.plot(np.log10(t1_ordered_i), t1_ordered_e, '-', color='#377eb8', alpha=0.4, linewidth=1.0, label='$T=1.0$ $J/k_{B}$, ordered')
plt.plot(np.log10(t1_unordered_i), t1_unordered_e, '-', color='#4daf4a', alpha=0.4, linewidth=1.0, label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(np.log10(t2_4_ordered_i), t2_4_ordered_e, '-', color='#e41a1c', alpha=0.4, linewidth=1.0, label='$T=2.4$ $J/k_{B}$, ordered')
plt.plot(np.log10(t2_4_unordered_i), t2_4_unordered_e, '-', color='#984ea3', alpha=0.4, linewidth=1.0, label='$T=2.4$ $J/k_{B}$, unordered')
plt.xlabel("Monte Carlo Cycles", fontsize=16)
plt.ylabel("Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()

plt.plot(np.log10(t1_ordered_i), t1_ordered_cum_e, '-', linewidth=2.0, color='#377eb8', label='$T=1.0$ $J/k_{B}$, ordered')
plt.plot(np.log10(t1_unordered_i), t1_unordered_cum_e, '-', linewidth=2.0, color='#4daf4a', label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(np.log10(t2_4_ordered_i), t2_4_ordered_cum_e, '-', linewidth=2.0, color='#e41a1c', label='$T=2.4$ $J/k_{B}$, ordered')
plt.plot(np.log10(t2_4_unordered_i), t2_4_unordered_cum_e, '-', linewidth=2.0, color='#984ea3', label='$T=2.4$ $J/k_{B}$, unordered')
plt.xlabel("Monte Carlo Cycles", fontsize=16)
plt.ylabel("Cumulative Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()



bins = 50 

plt.figure(figsize=(12, 6))

# Histogram for T = 1.0
plt.subplot(1, 2, 1)
plt.hist(t1_unordered_e, bins=bins, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.title('Energy Distribution at T = 1.0')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')

# Histogram for T = 2.4
plt.subplot(1, 2, 2)
plt.hist(t2_4_unordered_e, bins=bins, density=True, alpha=0.7, color='red', edgecolor='black')
plt.title('Energy Distribution at T = 2.4')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')

plt.tight_layout()
plt.show()


plt.plot(temp40, energy40, label="L=40")
plt.plot(temp40, energy60, label="L=60")
plt.plot(temp40, energy80, label="L=80")
plt.plot(temp40, energy100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Expected Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()

plt.plot(temp40, magnetization40, label="L=40")
plt.plot(temp40, magnetization60, label="L=60")
plt.plot(temp40, magnetization80, label="L=80")
plt.plot(temp40, magnetization100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Expected magnetization", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()


plt.plot(temp40, heat_cap40, label="L=40")
plt.plot(temp40, heat_cap60, label="L=60")
plt.plot(temp40, heat_cap80, label="L=80")
plt.plot(temp40, heat_cap100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Expected heat capacity", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()


plt.plot(temp40, sus40, label="L=40")
plt.plot(temp40, sus60, label="L=60")
plt.plot(temp40, sus80, label="L=80")
plt.plot(temp40, sus100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Expected Susceptibility", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()

# For problem 2
plt.plot(temp2, energy2, label="energy")
plt.legend()
plt.show()
plt.plot(temp2, magnetization2, label="mag")
plt.legend()
plt.show()
plt.plot(temp2, heat_cap2, label="heat cap")
plt.legend()
plt.show()
plt.plot(temp2, sus2, label="sus")
plt.legend()
plt.show()

















