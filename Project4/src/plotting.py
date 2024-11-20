import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

# Pre-computed
T10_MC_cycles_o, eps_T10_o, mean_eps_T10_o, mag_T10_o = np.loadtxt("txt_burn_in/energy_L20_T1.000000_ordered.txt", unpack=True)
T10_MC_cycles_u, eps_T10_u, mean_eps_T10_u, mag_T10_u = np.loadtxt("txt_burn_in/energy_L20_T1.000000_unordered.txt", unpack=True)
T24_MC_cycles_o, eps_T24_o, mean_eps_T24_o, mag_T24_o = np.loadtxt("txt_burn_in/energy_L20_T2.400000_ordered.txt", unpack=True)
T24_MC_cycles_u, eps_T24_u, mean_eps_T24_u, mag_T24_u = np.loadtxt("txt_burn_in/energy_L20_T2.400000_unordered.txt", unpack=True)

# Pre-computed
temp40, energy40, energy2_40, magnetisation40, magnetisation2_40, heat_cap40, sus40 = np.loadtxt("txt_heavy/L40_func_of_temp.txt", unpack=True, skiprows=1)
temp60, energy60, energy2_60, magnetisation60, magnetisation2_60, heat_cap60, sus60 = np.loadtxt("txt_heavy/L60_func_of_temp.txt", unpack=True, skiprows=1)
temp80, energy80, energy2_80, magnetisation80, magnetisation2_80, heat_cap80, sus80 = np.loadtxt("txt_heavy/L80_func_of_temp.txt", unpack=True, skiprows=1)
temp100, energy100, energy2_100, magnetisation100, magnetisation2_100, heat_cap100, sus100 = np.loadtxt("txt_heavy/L100_func_of_temp.txt", unpack=True, skiprows=1)

# Pre-computed: with 10% burn-in and 1 000 000
T10_MC_cycles_o_hist, eps_T10_o_hist, mean_eps_T10_o_hist, mag_T10_o_hist = np.loadtxt("txt_histogram/energy_L20_T1.000000_ordered.txt", unpack=True)
T10_MC_cycles_u_hist, eps_T10_u_hist, mean_eps_T10_u_hist, mag_T10_u_hist = np.loadtxt("txt_histogram/energy_L20_T1.000000_unordered.txt", unpack=True)
T24_MC_cycles_o_hist, eps_T24_o_hist, mean_eps_T24_o_hist, mag_T24_o_hist = np.loadtxt("txt_histogram/energy_L20_T2.400000_ordered.txt", unpack=True)
T24_MC_cycles_u_hist, eps_T24_u_hist, mean_eps_T24_u_hist, mag_T24_u_hist = np.loadtxt("txt_histogram/energy_L20_T2.400000_unordered.txt", unpack=True)


temp2, energy2, energy2_2, magnetisation2, magnetisation2_2, heat_cap2, sus2 = np.loadtxt("L2_func_of_temp.txt", unpack=True, skiprows=1)




# --------------- PROBLEM 4 ---------------
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
plt.scatter(temp2, energy2_2, label = r"Avg $\epsilon^2$", s=2, alpha=0.4)
plt.plot(temp2, E2 / 4**2, label = r'$\langle \epsilon^2 \rangle$')
plt.scatter(temp2, energy2, label = r"Avg $\epsilon$", s=2, alpha=0.4)
plt.plot(temp2, E_N, label = r'$\langle \epsilon \rangle$')
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize = 16)
plt.ylabel(r"[J, $J^2$]", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_energy_50000.pdf", format="pdf", bbox_inches="tight")
plt.show()

# Magnetisation
plt.scatter(temp2, magnetisation2, label = r"Avg m", s=2, alpha=0.4)
plt.plot(temp2, M_N, label = r'$\langle |m| \rangle$')
plt.scatter(temp2, magnetisation2_2, label = r"Avg $m^2$", s=2, alpha=0.4)
plt.plot(temp2, M2_N, label = r"$\langle m^2 \rangle $")
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize = 16)
plt.ylabel("[1]", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_mag_50000.pdf", format="pdf", bbox_inches="tight")
plt.show()

# Heat capacity
plt.scatter(temp2, heat_cap2, label = r"Avg $\frac{C_V}{N}$", s=2, alpha=0.4)
plt.plot(temp2, Cv_N, label = r"$\frac{C_V}{N} $")
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize = 16)
plt.ylabel("[1]", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_Cv_50000.pdf", format="pdf", bbox_inches="tight")
plt.show()

#Susceptibility
plt.scatter(temp2, sus2, label = r"Avg $\frac{\chi}{N}$", s=2, alpha=0.4)
plt.plot(temp2, chi_N, label = r"$\frac{\chi}{N} $")
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize = 16)
plt.ylabel("[1]", fontsize = 16)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.legend(fontsize = 16)
plt.grid()
# plt.savefig("2x2_susc_50000.pdf", format="pdf", bbox_inches="tight")
plt.show()




log_cycles = []
log_cycles.append(0)
for i in range(1, len(T10_MC_cycles_o)):
	log_cycles.append(np.log10(T10_MC_cycles_o[i]))

# --------------- PROBLEM 5 ---------------
# T = 1.0
plt.plot(log_cycles, eps_T10_u, '-', color='#377eb8', alpha=0.4, linewidth=1.0, label=r'Current $\epsilon$, unordered')
plt.plot(log_cycles, mean_eps_T10_u, '-', linewidth=2.0, color='#377eb8', label=r'Average $\langle \epsilon \rangle$, unordered')
plt.plot(log_cycles, eps_T10_o, '-', color='#4daf4a', alpha=0.4, linewidth=1.0, label=r'Current $\epsilon$, ordered')
plt.plot(log_cycles, mean_eps_T10_o, '-', linewidth=2.0, color='#4daf4a', label=r'Average $\langle \epsilon \rangle$, ordered')
plt.xlabel("log(Monte Carlo Cycles)", fontsize=16)
plt.ylabel("Energy [J]", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)   
plt.grid()
# plt.savefig("mc_cycles_vs_eps_T10.pdf")
plt.show()

# T = 2.4
plt.plot(log_cycles, eps_T24_u, '-', color='#e41a1c', alpha=0.4, linewidth=1.0,  label=r'Current $\epsilon$, unordered')
plt.plot(log_cycles, mean_eps_T24_u, '-', linewidth=2.0, color='#e41a1c', label=r'Average $\langle \epsilon \rangle$, unordered')
plt.plot(log_cycles, eps_T24_o, '-', color='#984ea3', alpha=0.4, linewidth=1.0, label=r'Current $\epsilon$, ordered')
plt.plot(log_cycles, mean_eps_T24_o, '-', linewidth=2.0, color='#984ea3', label=r'Average $\langle \epsilon \rangle$, ordered')
plt.xlabel("log(Monte Carlo Cycles)", fontsize=16)
plt.ylabel("Energy [J]", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)   
plt.grid()
# plt.savefig("mc_cycles_vs_eps_T24.pdf")
plt.show()





# --------------- PROBLEM 6 ---------------
bins = 120 
plt.figure(figsize=(12, 6))

# Histogram for T = 1.0
plt.subplot(1, 2, 1)
plt.hist(eps_T10_o_hist, bins=bins, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.title('Energy Distribution at T = 1.0')
plt.xlabel('Energy per Spin $\epsilon$')
plt.ylabel('Probability Density $p_{\epsilon}(\epsilon; T)$')
plt.grid()

# Histogram for T = 2.4
plt.subplot(1, 2, 2)
plt.hist(eps_T24_o_hist, bins=bins, density=True, alpha=0.7, color='red', edgecolor='black')
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
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize=16)
plt.ylabel(r"$\langle \epsilon \rangle$", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
plt.tight_layout()
# plt.savefig("temp_eps.pdf")
plt.show()

# Magnetisation
plt.plot(temp40, magnetisation40, label="L=40", marker='o')
plt.plot(temp40, magnetisation60, label="L=60", marker='o')
plt.plot(temp40, magnetisation80, label="L=80", marker='o')
plt.plot(temp40, magnetisation100, label="L=100", marker='o')
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize=16)
plt.ylabel(r"$\langle | m | \rangle $", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
plt.tight_layout()
# plt.savefig("temp_magnetisation.pdf")
plt.show()

# Heat capacity 
plt.plot(temp40, heat_cap40, label="L=40", marker='o')
plt.plot(temp40, heat_cap60, label="L=60", marker='o')
plt.plot(temp40, heat_cap80, label="L=80", marker='o')
plt.plot(temp40, heat_cap100, label="L=100", marker='o')
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize=16)
plt.ylabel(r"$\frac{C_V}{N} $", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
plt.tight_layout()
# plt.savefig("temp_heat_cap.pdf")
plt.show()

# Susceptibility
plt.plot(temp40, sus40, label="L=40", marker='o')
plt.plot(temp40, sus60, label="L=60", marker='o')
plt.plot(temp40, sus80, label="L=80", marker='o')
plt.plot(temp40, sus100, label="L=100", marker='o')
plt.xlabel(r'T [$Jk_B^{-1}$]', fontsize=16)
plt.ylabel(r"$\frac{\chi}{N} $", fontsize=16)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
plt.tight_layout()
# plt.savefig("temp_sus.pdf")
plt.show()





# --------------- PROBLEM 9 ---------------
L = np.array([40, 60, 80, 100])

# Susceptibility
T_c_X = np.array([temp40[np.argmax(sus40)],
				  temp40[np.argmax(sus60)],
				  temp40[np.argmax(sus80)],
				  temp40[np.argmax(sus100)]])  

# Heat capacity
T_c_Cv = np.array([temp40[np.argmax(heat_cap40)],
				   temp40[np.argmax(heat_cap60)],
				   temp40[np.argmax(heat_cap80)],
				   temp40[np.argmax(heat_cap100)]]) 



#Susceptibility
plt.plot(1 / L, T_c_X, label='Data points for $\chi$', marker='o', linestyle='None')
fit_X = linregress(1 / L, T_c_X)
plt.plot(1 / L, fit_X.slope / L + fit_X.intercept, label='2.3936 $L^{-1}$ + 2.2591 $Jk_B^{-1}$')
plt.xlabel('$L^{-1}$', fontsize=16)
plt.ylabel('$T_c$ [J $k_B^{-1}$]', fontsize=16)
plt.xticks(fontsize=13)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.tight_layout()
plt.grid()
# plt.savefig("problem9_susceptibility.pdf", format="pdf")
plt.show()

r_value_X = fit_X.rvalue
intercept_X = fit_X.intercept
slope_X = fit_X.slope
intercept_stderr_X = fit_X.intercept_stderr

print("\n")
print("---------- SUSCEPTIBILITY ----------")
print(f"Critical temperatures for L = [40, 60, 80, 100] based on results from susceptibility: {T_c_X}")
print(f"R² value for susceptibility fit:          {r_value_X**2:.4f}")
print(f"Intercept value for susceptibility fit:   {intercept_X:.4f}")
print(f"Uncertainty value for susceptibility fit: {intercept_stderr_X:.4f}")
print(f"Slope for susceptibility fit:             {slope_X:.4f}")

plt.plot(1 / L, T_c_Cv, label=r'Data points for $\frac{C_V}{N}$', marker='o', linestyle='None')
fit_Cv = linregress(1 / L, T_c_Cv)
plt.plot(1 / L, fit_Cv.slope / L + fit_Cv.intercept, label='1.8474 $L^{-1}$ + 2.2529 $Jk_B^{-1}$')
plt.xlabel('$L^{-1}$', fontsize=16)
plt.ylabel('$T_c$ [J $k_B^{-1}$]', fontsize=16)
plt.xticks(fontsize=13)
plt.yticks(fontsize=16)
plt.legend(fontsize=16)
plt.grid()
plt.tight_layout()
# plt.savefig("problem9_heat_cap.pdf", format="pdf")
plt.show()


r_value_Cv = fit_Cv.rvalue
intercept_Cv = fit_Cv.intercept
slope_Cv = fit_Cv.slope
intercept_stderr_Cv = fit_Cv.intercept_stderr

print("\n")
print("---------- HEAT CAPACITY ----------")
print(f"Critical temperatures for L = [40, 60, 80, 100] based on results from heat capacity: {T_c_X}")
print(f"R² value for heat capacity fit:          {r_value_Cv**2:.4f}")
print(f"Intercept value for heat capacity fit:   {intercept_Cv:.4f}")
print(f"Uncertainty value for heat capacity fit: {intercept_stderr_Cv:.4f}")
print(f"Slope for heat capacity fit:             {slope_Cv:.4f}")

