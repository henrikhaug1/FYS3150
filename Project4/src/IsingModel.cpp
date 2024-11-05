#include <iostream>
#include "IsingModel.hpp"

IsingModel::IsingModel(int L_in, double temp_in, double J_in)
    : L(L_in), T(temp_in), J(J_in), spins(L_in, L_in)
{
	//initialize spins
	spins.imbue([]() { return arma::randi<int>(arma::distr_param(0, 1)) * 2 - 1; });

}

double IsingModel::delta_energy(int i, int j)
{
	int left = spins(i, (j - 1 + L) % L);
    int right = spins(i, (j + 1) % L);
    int up = spins((i - 1 + L) % L, j);
    int down = spins((i + 1) % L, j);

    int s = spins(i, j);
    int sum_neighbors = left + right + up + down;

    // Energy change if spin at (i, j) is flipped
    return 2.0 * J * s * sum_neighbors;
}

void IsingModel::monte_carlo_step()
{
	static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_pos(0, L - 1);
    std::uniform_real_distribution<double> dist_prob(0.0, 1.0);

    for (int n = 0; n < L * L; n++)
    {
        int i = dist_pos(rng);
        int j = dist_pos(rng);

        double dE = delta_energy(i, j);

        if (dE <= 0)
        {
            spins(i, j) *= -1; // Flip spin
        }
        else
        {
            double p = std::exp(-dE / T);
            if (dist_prob(rng) < p)
            {
                spins(i, j) *= -1; // Flip spin
            }
        }
    }
}

void IsingModel::metropolis(int num_steps)
{
    int equilibration_steps = num_steps / 10; // 10% of steps for equilibration
    int total_steps = equilibration_steps + num_steps;

    double E_sum = 0.0;
    double E2_sum = 0.0;
    double M_sum = 0.0;
    double M2_sum = 0.0;

    for (int step = 0; step < total_steps; step++)
    {
        monte_carlo_step();

        if (step >= equilibration_steps)
        {
            double E = total_energy(spins);
            double M = magnetisation();

            E_sum += E;
            E2_sum += E * E;
            M_sum += std::abs(M); // Use absolute value if needed
            M2_sum += M * M;
        }
    }

    int N = num_steps;
    double E_mean = E_sum / N;
    double E2_mean = E2_sum / N;
    double M_mean = M_sum / N;
    double M2_mean = M2_sum / N;

    // Normalize by the number of spins
    int num_spins = L * L;

    // Assign to class variables
    average_energy = E_mean / num_spins;
    average_magnetisation = M_mean / num_spins;
    specific_heat = (E2_mean - E_mean * E_mean) / (T * T * num_spins);
    susceptibility = (M2_mean - M_mean * M_mean) / (T * num_spins);
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
    int num_states = 1 << (L * L);
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
