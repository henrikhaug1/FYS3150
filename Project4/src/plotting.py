import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress


T10_MC_cycles_o, eps_T10_o, mean_eps_T10_o, mag_T10_o = np.loadtxt("energy_L20_T1.000000_ordered.txt", unpack=True)
T10_MC_cycles_u, eps_T10_u, mean_eps_T10_u, mag_T10_u = np.loadtxt("energy_L20_T1.000000_unordered.txt", unpack=True)
T24_MC_cycles_o, eps_T24_o, mean_eps_T24_o, mag_T24_o = np.loadtxt("energy_L20_T2.400000_ordered.txt", unpack=True)
T24_MC_cycles_u, eps_T24_u, mean_eps_T24_u, mag_T24_u = np.loadtxt("energy_L20_T2.400000_unordered.txt", unpack=True)



temp2, energy2, energy2_2, magnetisation2, magnetisation2_2, heat_cap2, sus2 = np.loadtxt("L2_func_of_temp.txt", unpack=True, skiprows=1)
temp40, energy40, energy2_40, magnetisation40, magnetisation2_40, heat_cap40, sus40 = np.loadtxt("txt_files/L40_func_of_temp.txt", unpack=True, skiprows=1)
temp60, energy60, energy2_60, magnetisation60, magnetisation2_60, heat_cap60, sus60 = np.loadtxt("txt_files/L60_func_of_temp.txt", unpack=True, skiprows=1)
temp80, energy80, energy2_80, magnetisation80, magnetisation2_80, heat_cap80, sus80 = np.loadtxt("txt_files/L80_func_of_temp.txt", unpack=True, skiprows=1)
temp100, energy100, energy2_100, magnetisation100, magnetisation2_100, heat_cap100, sus100 = np.loadtxt("txt_files/L100_func_of_temp.txt", unpack=True, skiprows=1)


temp40_fine, heat_cap40_fine, sus40_fine = np.loadtxt("txt_files/L40_func_of_temp_fine.txt", unpack=True, skiprows=1)
temp60_fine, heat_cap60_fine, sus60_fine = np.loadtxt("txt_files/L60_func_of_temp_fine.txt", unpack=True, skiprows=1)
temp80_fine, heat_cap80_fine, sus80_fine = np.loadtxt("txt_files/L80_func_of_temp_fine.txt", unpack=True, skiprows=1)
temp100_fine, heat_cap100_fine, sus100_fine = np.loadtxt("txt_files/L100_func_of_temp_fine.txt", unpack=True, skiprows=1)



# --------------- PROBLEM 2 ---------------
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


# Energy
plt.plot(temp2, energy2_2, label = r"Avg $\epsilon^2$")
plt.plot(temp2, E2 / 4**2, label = r'$\langle epsilon^2 \rangle$')
plt.plot(temp2, energy2, label = r"Avg $\epsilon$")
plt.plot(temp2, E_N, label = r'$\langle epsilon \rangle$')
plt.xlabel('T', fontsize = 16)
plt.ylabel(r"J, $J^2$", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_energy_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

# Magnetisation
plt.plot(temp2, magnetisation2, label = r"Avg m")
plt.plot(temp2, M_N, label = r'$\langle |m| \rangle$')
plt.plot(temp2, magnetisation2_2, label = r"Avg $m^2$")
plt.plot(temp2, M2_N, label = r"$\langle m^2 \rangle $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_mag_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

# Heat capacity
plt.plot(temp2, heat_cap2, label = r"Avg $\frac{C_V}{N}$")
plt.plot(temp2, Cv_N, label = r"$\frac{C_V}{N} $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_Cv_500.pdf", format="pdf", bbox_inches="tight")
plt.show()

#Susceptibility
plt.plot(temp2, sus2, label = r"Avg $\frac{\chi}{N}$")
plt.plot(temp2, chi_N, label = r"$\frac{\chi}{N} $")
plt.xlabel('T', fontsize = 16)
plt.ylabel("1", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_susc_500.pdf", format="pdf", bbox_inches="tight")
plt.show()


log_cycles = []
log_cycles.append(0)
for i in range(1, len(T10_MC_cycles_o)):
	log_cycles.append(np.log10(T10_MC_cycles_o[i]))

# --------------- PROBLEM 5 ---------------
plt.plot(log_cycles, eps_T10_u, '-', color='#377eb8', alpha=0.4, linewidth=1.0)
plt.plot(log_cycles, eps_T10_o, '-', color='#4daf4a', alpha=0.4, linewidth=1.0)
plt.plot(log_cycles, eps_T24_u, '-', color='#e41a1c', alpha=0.4, linewidth=1.0)
plt.plot(log_cycles, eps_T24_o, '-', color='#984ea3', alpha=0.4, linewidth=1.0)
plt.plot(log_cycles, mean_eps_T10_u, '-', linewidth=2.0, color='#377eb8', label='$T=1.0$ $J/k_{B}$, unordered')
plt.plot(log_cycles, mean_eps_T10_o, '-', linewidth=2.0, color='#4daf4a', label='$T=1.0$ $J/k_{B}$, ordered')
plt.plot(log_cycles, mean_eps_T24_u, '-', linewidth=2.0, color='#e41a1c', label='$T=2.4$ $J/k_{B}$, unordered')
plt.plot(log_cycles, mean_eps_T24_o, '-', linewidth=2.0, color='#984ea3', label='$T=2.4$ $J/k_{B}$, ordered')
plt.xlabel("log(Monte Carlo Cycles)", fontsize=16)
plt.ylabel("Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
# plt.savefig("mc_cycles_vs_eps.pdf")
plt.show()



# --------------- PROBLEM 6 ---------------
bins = 50 
plt.figure(figsize=(12, 6))

# Histogram for T = 1.0
plt.subplot(1, 2, 1)
plt.hist(eps_T10_o, bins=bins, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.title('Energy Distribution at T = 1.0')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')
plt.grid()

# Histogram for T = 2.4
plt.subplot(1, 2, 2)
plt.hist(eps_T24_o, bins=bins, density=True, alpha=0.7, color='red', edgecolor='black')
plt.title('Energy Distribution at T = 2.4')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')
plt.grid()

plt.tight_layout()
# plt.savefig("eps_distribution_hist.pdf")
plt.show()



# --------------- PROBLEM 8 ---------------
# Energy
plt.plot(temp40, energy40, label="L=40", marker='o')
plt.plot(temp40, energy60, label="L=60", marker='o')
plt.plot(temp40, energy80, label="L=80", marker='o')
plt.plot(temp40, energy100, label="L=100", marker='o')
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Energy", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
# plt.savefig("temp_eps.pdf")
plt.show()

# Magnetisation
plt.plot(temp40, magnetisation40, label="L=40", marker='o')
plt.plot(temp40, magnetisation60, label="L=60", marker='o')
plt.plot(temp40, magnetisation80, label="L=80", marker='o')
plt.plot(temp40, magnetisation100, label="L=100", marker='o')
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Magnetization", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
# plt.savefig("temp_magnetisation.pdf")
plt.show()

# Heat capacity 
plt.plot(temp40, heat_cap40, label="L=40", marker='o')
plt.plot(temp40, heat_cap60, label="L=60", marker='o')
plt.plot(temp40, heat_cap80, label="L=80", marker='o')
plt.plot(temp40, heat_cap100, label="L=100", marker='o')
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Heat capacity", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
# plt.savefig("temp_heat_cap.pdf")
plt.show()

# Susceptibility
plt.plot(temp40, sus40, label="L=40", marker='o')
plt.plot(temp40, sus60, label="L=60", marker='o')
plt.plot(temp40, sus80, label="L=80", marker='o')
plt.plot(temp40, sus100, label="L=100", marker='o')
plt.xlabel("Temperature", fontsize=16)
plt.ylabel("Susceptibility", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
# plt.savefig("temp_sus.pdf")
plt.show()





# --------------- PROBLEM 9 ---------------
L = np.array([40, 60, 80, 100])

# Susceptibility
T_c_X = np.array([temp40_fine[np.argmax(sus40_fine)],
				  temp40_fine[np.argmax(sus60_fine)],
				  temp40_fine[np.argmax(sus80_fine)],
				  temp40_fine[np.argmax(sus100_fine)]])  

# Heat capacity
T_c_Cv = np.array([temp40_fine[np.argmax(heat_cap40_fine)],
				   temp40_fine[np.argmax(heat_cap60_fine)],
				   temp40_fine[np.argmax(heat_cap80_fine)],
				   temp40_fine[np.argmax(heat_cap100_fine)]]) 

plt.figure(figsize=(12, 6))

# Left subplot
plt.subplot(1, 2, 1)
plt.plot(1 / L, T_c_Cv, label='Data points for $C_V$', marker='o', linestyle='None')
fit_CV = linregress(1 / L, T_c_Cv)
slope_CV = fit_CV.slope
intercept_CV = fit_CV.intercept
plt.plot(1 / L, slope_CV / L + intercept_CV, label='1.078 $L^{-1}$ + 2.261 $Jk_B^{-1}$  (???)')
plt.xlabel('$L^{-1}$')
plt.ylabel('$T_c$ [J $k_B^{-1}$]')
plt.legend()
plt.grid()  # Apply grid to the left subplot

# Right subplot
plt.subplot(1, 2, 2)
plt.plot(1 / L, T_c_X, label='Data points for $X$', marker='o', linestyle='None')
fit_X = linregress(1 / L, T_c_X)
slope_X = fit_X.slope
intercept_X = fit_X.intercept
plt.plot(1 / L, slope_X / L + intercept_X, label='1.078 $L^{-1}$ + 2.261 $Jk_B^{-1}$   (???)')
plt.xlabel('$L^{-1}$')
plt.ylabel('$T_c$ [J $k_B^{-1}$]')
plt.legend()
plt.grid()  # Apply grid to the right subplot

plt.tight_layout()
#plt.savefig('problem9.pdf', format='pdf')
plt.show()








