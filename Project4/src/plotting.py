import matplotlib.pyplot as plt
import numpy as np

t1_ordered = np.loadtxt("energy_L20_T1.000000_ordered.txt", skipcols=1, unpack=True)
t1_unordered = np.loadtxt("energy_L20_T1.000000_unordered.txt", skipcols=1, unpack=True)
t2_4_ordered = np.loadtxt("energy_L20_T2.400000_ordered.txt", skipcols=1, unpack=True)
t2_4_unordered = np.loadtxt("energy_L20_T2.400000_unordered.txt", skipcols=1, unpack=True)


plt.plot(n_MC_cycles, eps_T10_u, '-', color='#377eb8', alpha=0.4, linewidth=1.0)
plt.plot(n_MC_cycles, eps_T10_o, '-', color='#4daf4a', alpha=0.4, linewidth=1.0)
plt.plot(n_MC_cycles, eps_T24_u, '-', color='#e41a1c', alpha=0.4, linewidth=1.0)
plt.plot(n_MC_cycles, eps_T24_o, '-', color='#984ea3', alpha=0.4, linewidth=1.0)

plt.plot(n_MC_cycles, mean_eps_T10_u, '-', linewidth=2.0, color='#377eb8', label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(n_MC_cycles, mean_eps_T10_o, '-', linewidth=2.0, color='#4daf4a', label='$T=1.0$ $J/k_{B}$, ordered')
plt.plot(n_MC_cycles, mean_eps_T24_u, '-', linewidth=2.0, color='#e41a1c', label='$T=2.4$ $J/k_{B}$, unordered')
plt.plot(n_MC_cycles, mean_eps_T24_o, '-', linewidth=2.0, color='#984ea3', label='$T=2.4$ $J/k_{B}$, ordered')