#include <iostream>
#include <vector>
#include "IsingModel.hpp"
#include <iomanip>

IsingModel::IsingModel(int L_in, double temp_in, double J_in, bool ordered)
    : L(L_in), T(temp_in), J(J_in), spins(L_in, L_in)
{
    if (ordered)
    {
        // Initialize spins to all +1 (ordered state)
        spins.ones();
    }
    else
    {
        // Initialize spins randomly to +1 or -1 (unordered state)
        spins.imbue([]() { return arma::randi<int>(arma::distr_param(0, 1)) * 2 - 1; });
    }
}





double IsingModel::delta_energy(int i, int j)
{
	int left = spins(i, (j - 1 + L) % L);
    int right = spins(i, (j + 1) % L);
    int up = spins((i - 1 + L) % L, j);
    int down = spins((i + 1) % L, j);

    int s = spins(i, j);
    int sum_neighbors = left + right + up + down;

    double dE = 2.0 * J * s * sum_neighbors;
    return dE;
}



void IsingModel::monte_carlo_step()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_pos(0, L - 1);
    std::uniform_real_distribution<double> dist_prob(0.0, 1.0);
    double beta = 1./T;

    std::map<int, double> boltzmann;
    boltzmann[-8] = std::exp(8 * beta);
    boltzmann[-4] = std::exp(4 * beta);
    boltzmann[0] = 1.;
    boltzmann[4] = std::exp(-4 * beta);
    boltzmann[8] = std::exp(-8 * beta);

    for (int n = 0; n < L * L; n++)
    {
        // Select a random spin (i, j)
        int i = dist_pos(rng);
        int j = dist_pos(rng);

        double dE;
        double boltzman_factor;
        double acceptance_prob;

        if(L<=2)
        {
            dE = delta_energy(i, j);
            boltzman_factor = std::exp(-dE / T);
            acceptance_prob = std::min(1., boltzman_factor);
        }
        else
        {
            dE = delta_energy(i, j);
            acceptance_prob = std::min(1., boltzmann[dE]);
        }

        // Generate a random number and decide to accept or reject
        double r = dist_prob(rng);
        if (r < acceptance_prob)
        {
            spins(i, j) *= -1; // Flip the spin
        }
    }
}






void IsingModel::metropolis(int num_cycles, std::vector<double>& energies, std::vector<double>& cumulative_energies, std::vector<double>& magnetisations)
{
    int equilibration_steps = num_cycles / 10; // 10% of steps for equilibration
    // int equilibration_steps = 0; //For determining the burn-in time
    int N = L * L;

    // Clear previous results
    energies.clear();
    cumulative_energies.clear();
    magnetisations.clear();

    double E_sum = 0.0;
    double M_sum = 0.0;
    double E2_sum = 0.0;
    double M2_sum = 0.0;

    for (int cycle = 0; cycle < num_cycles; cycle++)
    {
        // Run a Monte Carlo step (complete one lattice update)
        monte_carlo_step();

        // After equilibration, calculate and record quantities of interest
        if (cycle >= equilibration_steps)
        {
            double E = total_energy(spins);
            double M = magnetisation();

            E_sum += E;
            E2_sum += E * E;
            M_sum += std::abs(M);
            M2_sum += M * M;

            int adjusted_cycle = cycle - equilibration_steps + 1;

            // Store energy per spin and cumulative averages
            double E_per_spin = E / N;
            energies.push_back(E_per_spin);

            double avg_E_per_spin = (E_sum / adjusted_cycle) / N;
            cumulative_energies.push_back(avg_E_per_spin);

            // Store magnetisation per spin
            double M_per_spin = M / N;
            magnetisations.push_back(M_per_spin);
        }
    }

    // Final averages over the MCMC cycles (post-equilibration)
    int measured_steps = num_cycles - equilibration_steps;
    average_energy = E_sum / measured_steps / N;
    average_energy2 = E2_sum / measured_steps / (N * N);
    average_magnetisation = M_sum / measured_steps / N;
    average_magnetisation2 = M2_sum / measured_steps / (N * N);
    specific_heat = N * (average_energy2 - average_energy * average_energy) / (T * T);
    susceptibility = N * (average_magnetisation2 - average_magnetisation * average_magnetisation) / (T);
}





double IsingModel::total_energy(const arma::Mat<int>& spin_config)
{
    double E = 0.0;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            int s = spin_config(i, j);
            int right = spin_config(i, (j + 1) % L);
            int down = spin_config((i + 1) % L, j);

            // Only summing over right and down neighbours to avoid double counting
            E -= J * s * (right + down); 
        }
    }
    return E;
}


double IsingModel::energy_per_spin()
{
	return total_energy(spins) / (L * L);
}




double IsingModel::magnetisation()
{
    int M = arma::accu(spins);
    return static_cast<double>(M);
}




double IsingModel::magnetisation_per_spin()
{
	return magnetisation() / (L * L);
}





double IsingModel::partition_function()
{
    double Z = 0.0;
    int num_states = 1 << (L * L); //bitwise operation equivalent to 2^(L*L)
    arma::Mat<int> original_spins = spins; // Save the original spins
    arma::Mat<int> spin_config(L, L);
    double beta = 1.0 / T;

    for (int state = 0; state < num_states; state++)
    {
        // Set spin configuration for each possible state
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < L; j++)
            {
                int bit_index = i * L + j;
                spin_config(i, j) = ((state >> bit_index) & 1) ? 1 : -1;
            }
        }

        spins = spin_config; // Temporarily set spins to the new configuration

        // Calculate energy for the current configuration
        double E = total_energy(spins);
        Z += std::exp(-beta * E);
    }

    spins = original_spins; // Restore original spins
    return Z;
}



double IsingModel::probability_state()
{
	double beta = 1/(k_b * T);
	double E = total_energy(spins);
	double Z = partition_function();

	double probability = (1.0 / Z) * exp(-beta * E);

	return probability;

}


