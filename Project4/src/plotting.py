import matplotlib.pyplot as plt
import numpy as np

t1_ordered_i, t1_ordered_e, t1_ordered_cum_e = np.loadtxt("energy_L20_T1.000000_ordered.txt", skiprows=1, unpack=True)
t1_unordered_i, t1_unordered_e, t1_unordered_cum_e = np.loadtxt("energy_L20_T1.000000_unordered.txt", skiprows=1, unpack=True)
t2_4_ordered_i, t2_4_ordered_e, t2_4_ordered_cum_e = np.loadtxt("energy_L20_T2.400000_ordered.txt", skiprows=1, unpack=True)
t2_4_unordered_i, t2_4_unordered_e, t2_4_unordered_cum_e = np.loadtxt("energy_L20_T2.400000_unordered.txt", skiprows=1, unpack=True)


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

plt.plot(np.log10(t1_ordered_i), t1_ordered_cum_e, '-', linewidth=2.0, color='#377eb8', label='$T=1.0$ $J/k_{B}$, onordered')
plt.plot(np.log10(t1_unordered_i), t1_unordered_cum_e, '-', linewidth=2.0, color='#4daf4a', label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(np.log10(t2_4_ordered_i), t2_4_ordered_cum_e, '-', linewidth=2.0, color='#e41a1c', label='$T=2.4$ $J/k_{B}$, ordered')
plt.plot(np.log10(t2_4_unordered_i), t2_4_unordered_cum_e, '-', linewidth=2.0, color='#984ea3', label='$T=2.4$ $J/k_{B}$, unordered')
plt.xlabel("Monte Carlo Cycles", fontsize=16)
plt.ylabel("Cumulative Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()