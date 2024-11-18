import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

T10_MC_cycles_o, eps_T10_o, mean_eps_T10_o, mag_T10_o = np.loadtxt("energy_L20_T1.000000_ordered.txt", unpack=True)
T10_MC_cycles_u, eps_T10_u, mean_eps_T10_u, mag_T10_u = np.loadtxt("energy_L20_T1.000000_unordered.txt", unpack=True)
T24_MC_cycles_o, eps_T24_o, mean_eps_T24_o, mag_T24_o = np.loadtxt("energy_L20_T2.400000_ordered.txt", unpack=True)
T24_MC_cycles_u, eps_T24_u, mean_eps_T24_u, mag_T24_u = np.loadtxt("energy_L20_T2.400000_unordered.txt", unpack=True)



# ---------- testing ---------
# temp2, energy2, energy2_2, magnetization2, magnetization2_2, heat_cap2, sus2 = np.loadtxt("L2_func_of_temp.txt", unpack=True, skiprows=1)
# temp4, energy4, energy2_4, magnetization4, magnetization2_4, heat_cap4, sus4 = np.loadtxt("L4_func_of_temp.txt", unpack=True, skiprows=1)
# temp6, energy6, energy2_6, magnetization6, magnetization2_6, heat_cap6, sus6 = np.loadtxt("L6_func_of_temp.txt", unpack=True, skiprows=1)
# temp8, energy8, energy2_8, magnetization8, magnetization2_8, heat_cap8, sus8 = np.loadtxt("L8_func_of_temp.txt", unpack=True, skiprows=1)
# temp10, energy10, energy2_10, magnetization10, magnetization2_10, heat_cap10, sus10 = np.loadtxt("L10_func_of_temp.txt", unpack=True, skiprows=1)
# temp15, energy15, energy2_15, magnetization15, magnetization2_15, heat_cap15, sus15 = np.loadtxt("L15_func_of_temp.txt", unpack=True, skiprows=1)
# temp20, energy20, energy2_20, magnetization20, magnetization2_20, heat_cap20, sus20 = np.loadtxt("L20_func_of_temp.txt", unpack=True, skiprows=1)




temp2, energy2, energy2_2, magnetization2, magnetization2_2, heat_cap2, sus2 = np.loadtxt("L2_func_of_temp.txt", unpack=True, skiprows=1)
temp40, energy40, energy2_40, magnetization40, magnetization2_40, heat_cap40, sus40 = np.loadtxt("L40_func_of_temp.txt", unpack=True, skiprows=1)
temp60, energy60, energy2_60, magnetization60, magnetization2_60, heat_cap60, sus60 = np.loadtxt("L60_func_of_temp.txt", unpack=True, skiprows=1)
temp80, energy80, energy2_80, magnetization80, magnetization2_80, heat_cap80, sus80 = np.loadtxt("L80_func_of_temp.txt", unpack=True, skiprows=1)
temp100, energy100, energy2_100, magnetization100, magnetization2_100, heat_cap100, sus100 = np.loadtxt("L100_func_of_temp.txt", unpack=True, skiprows=1)



plt.plot(np.log10(T10_MC_cycles_o), eps_T10_u, '-', color='#377eb8', alpha=0.4, linewidth=1.0)
plt.plot(np.log10(T10_MC_cycles_o), eps_T10_o, '-', color='#4daf4a', alpha=0.4, linewidth=1.0)
plt.plot(np.log10(T10_MC_cycles_o), eps_T24_u, '-', color='#e41a1c', alpha=0.4, linewidth=1.0)
plt.plot(np.log10(T10_MC_cycles_o), eps_T24_o, '-', color='#984ea3', alpha=0.4, linewidth=1.0)
plt.plot(np.log10(T10_MC_cycles_o), mean_eps_T10_u, '-', linewidth=2.0, color='#377eb8', label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(np.log10(T10_MC_cycles_o), mean_eps_T10_o, '-', linewidth=2.0, color='#4daf4a', label='$T=1.0$ $J/k_{B}$, ordered')
plt.plot(np.log10(T10_MC_cycles_o), mean_eps_T24_u, '-', linewidth=2.0, color='#e41a1c', label='$T=2.4$ $J/k_{B}$, unordered')
plt.plot(np.log10(T10_MC_cycles_o), mean_eps_T24_o, '-', linewidth=2.0, color='#984ea3', label='$T=2.4$ $J/k_{B}$, ordered')
plt.xlabel("log(Monte Carlo Cycles)", fontsize=16)
plt.ylabel("Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()

bins = 50 

plt.figure(figsize=(12, 6))

# Histogram for T = 1.0
plt.subplot(1, 2, 1)
plt.hist(eps_T10_o, bins=bins, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.title('Energy Distribution at T = 1.0')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')

# Histogram for T = 2.4
plt.subplot(1, 2, 2)
plt.hist(eps_T24_o, bins=bins, density=True, alpha=0.7, color='red', edgecolor='black')
plt.title('Energy Distribution at T = 2.4')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')

plt.tight_layout()
plt.show()



#plt.plot(temp40, energy2, label="L=2")
plt.plot(temp40, energy40, label="L=40")
plt.plot(temp40, energy60, label="L=60")
plt.plot(temp40, energy80, label="L=80")
plt.plot(temp40, energy100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()




#plt.plot(temp2, magnetization2, label="L=2")
plt.plot(temp40, magnetization40, label="L=40")
plt.plot(temp40, magnetization60, label="L=60")
plt.plot(temp40, magnetization80, label="L=80")
plt.plot(temp40, magnetization100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Magnetization", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()



#plt.plot(temp2, heat_cap2, label="L=2")
plt.plot(temp40, heat_cap40, label="L=40")
plt.plot(temp40, heat_cap60, label="L=60")
plt.plot(temp40, heat_cap80, label="L=80")
plt.plot(temp40, heat_cap100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Heat capacity", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()




#plt.plot(temp2, sus2, label="L=2")
plt.plot(temp40, sus40, label="L=40")
plt.plot(temp40, sus60, label="L=60")
plt.plot(temp40, sus80, label="L=80")
plt.plot(temp40, sus100, label="L=100")
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Susceptibility", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.show()

# For problem 2
k = 1 # 1.380649 * 10**(-23)
T = temp2
b = 1 / (k * T)
Z = 2 *np.exp(8 * b) + 2 * np.exp(-8*b) + 12

E = (1 / Z) * 16 * (np.exp(-8 *b) - np.exp(8 * b)) #Expectation values
E2 = (1 / Z) * 128 * (np.exp(-8 *b) + np.exp(8 * b))

E_N = E / 4

M = (8 / Z) * (np.exp(8 * b) + 2) #Expectation values
M2 = (32 / Z) * (np.exp(8 * b) + 1)

M_N = M / 4
M2_N = M2 / 4**2

Cv_N = (b / (4 * T)) * (E2 - E**2) #Specific heat capacity
chi_N = (b / 4) * (M2 - M**2)  #Magnetic susceptibility

plt.plot(temp2, energy2_2, label = r"Avg $\epsilon^2$")
plt.plot(temp2, E2 / 4**2, label = r'$\langle epsilon^2 \rangle$')
plt.plot(temp2, energy2, label = r"Avg $\epsilon$")
plt.plot(temp2, E_N, label = r'$\langle epsilon \rangle$')
plt.xlabel('T', fontsize = 16)
plt.ylabel(r"J, $J^2$", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.savefig("2x2_energy_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

plt.plot(temp2, magnetization2, label = r"Avg m")
plt.plot(temp2, M_N, label = r'$\langle |m| \rangle$')
plt.plot(temp2, magnetization2_2, label = r"Avg $m^2$")
plt.plot(temp2, M2_N, label = r"$\langle m^2 \rangle $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.savefig("2x2_mag_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

plt.plot(temp2, heat_cap2, label = r"Avg $\frac{C_V}{N}$")
plt.plot(temp2, Cv_N, label = r"$\frac{C_V}{N} $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.savefig("2x2_Cv_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

plt.plot(temp2, sus2, label = r"Avg $\frac{\chi}{N}$")
plt.plot(temp2, chi_N, label = r"$\frac{\chi}{N} $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.savefig("2x2_susc_500.pdf", format="pdf", bbox_inches="tight")
plt.show()


"""

def critical_temperature(lattice_sizes):

    T_c_inf = 2.269
    L_inverse = 1. / lattice_sizes
    a = 1
   	T_c = a * L_inverse + T_c_inf

    return T_c



# Given values
T_c_list = np.array([2.2940, 2.2857, 2.2815, 2.2790])
lattice_sizes = np.array([40, 60, 80, 100])
temps = np.arange(2.1, 2.4, 0.01)

# Plot the horizontal line for the infinite lattice critical temperature
plt.axhline(y=T_c_inf, color='r', linestyle='--', label=f"$T_c$ (infinite) = {T_c_inf}")

# Scatter plot of T_c values for finite lattice sizes
plt.scatter(lattice_sizes, T_c_list, color='b', label="Finite Lattice T_c")

# Labeling and display
plt.xlabel("Lattice Size")
plt.ylabel("Critical Temperature $T_c$")
plt.legend()
plt.show()
"""


# For problem 9
#lattice_sizes = np.array([40, 60, 80, 100])
#heat_cap_lists = np.array([heat_cap40, heat_cap60, heat_cap80, heat_cap100])

"""
for i in range(1, len(heat_cap40)):
	diff = 0
	idx = 0
	current_diff = abs(heat_cap40[i-1] - heat_cap[i])
	if current_diff > diff:
		diff = current_diff
		idx = i

T_c_estimate = temp40[i]
print(T_c_estimate)
"""

"""
max_sus_idx = [np.argmax(sus40), np.argmax(sus60), np.argmax(sus80), np.argmax(sus100)]
max_temp = [temp40[max_sus_idx[0]], temp60[max_sus_idx[1]], temp80[max_sus_idx[2]], temp100[max_sus_idx[3]]]

L_inverse = np.array([1./40, 1./60, 1./80, 1./100])

coefficients = np.polyfit(L_inverse, max_temp, 1)
slope, intercept = coefficients
a = slope

print(a)

plt.scatter(L_inverse, max_temp, label='$T_c$')
plt.plot(L_inverse, intercept + slope * L_inverse, 'r--', label='a')
plt.xlabel('1/L')
plt.ylabel('T_c(L)')
plt.title('Linear Regression of T_c(L) vs 1/L')
plt.legend()
plt.show()

print(intercept)
"""














