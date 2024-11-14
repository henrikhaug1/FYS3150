#include <iostream>
#include <vector>
#include "IsingModel.hpp"

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

    double delta_e = 2.0 * J * s * sum_neighbors;
    return delta_e;
}
/*
std::vector<double> IsingModel::delta_energy_big(int i, int j)
{

    int left = spins(i, (j - 1 + L) % L);
    int right = spins(i, (j + 1) % L);
    int up = spins((i - 1 + L) % L, j);
    int down = spins((i + 1) % L, j);

    std::vector<int> positions = {left, right, up, down};
    int count_neg = 0;

    for(int k = 0; k < 4; k++)
    {
        if( positions[k] < 0)
        {
            count_neg += 1;
        }
    }

    std::vector<double> possible_dE = {-8*J, -4*J, 0, 4*J, 8*J};
    std::vector<double> possible_boltzman_fac = {std::exp(-possible_dE[0]/T), std::exp(-possible_dE[1]/T), 1, std::exp(-possible_dE[3]/T), std::exp(-possible_dE[4]/T)};


    double dE;
    double boltzman_fac;
    if(count_neg == 4)
    {
        dE = possible_dE[0];
        boltzman_fac = possible_boltzman_fac[0];
    }
    else if(count_neg == 3)
    {
        dE = possible_dE[1];
        boltzman_fac = possible_boltzman_fac[1];
    }
    else if(count_neg == 2)
    {
        dE = possible_dE[2];
        boltzman_fac = possible_boltzman_fac[2];
    }
    else if(count_neg == 1)
    {
        dE = possible_dE[3];
        boltzman_fac = possible_boltzman_fac[3];
    }
    else if(count_neg == 0)
    {
        dE = possible_dE[4];
        boltzman_fac = possible_boltzman_fac[4];
    }

    return {dE, boltzman_fac};
}
*/


void IsingModel::monte_carlo_step()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist_pos(0, L - 1);
    std::uniform_real_distribution<double> dist_prob(0.0, 1.0);

    for (int n = 0; n < L * L; n++)
    {
        // Select a random spin (i, j) and attempt to flip it
        int i = dist_pos(rng);
        int j = dist_pos(rng);

        // Calculate the energy difference for flipping this spin
        double dE = delta_energy(i, j);

        // Calculate the acceptance probability p(s') / p(s)
        double acceptance_prob = std::exp(-dE / T);

        // Generate a random number and decide to accept or reject
        double r = dist_prob(rng);
        if (r < acceptance_prob)
        {
            spins(i, j) *= -1; // Flip the spin
        }
    }
}



/*
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
*/




void IsingModel::metropolis(int num_cycles, std::vector<double>& energies, std::vector<double>& cumulative_energies, std::vector<double>& magnetisations)
{
    int equilibration_steps = num_cycles / 10; // 10% of steps for equilibration
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
    average_magnetisation = M_sum / measured_steps / N;
    specific_heat = (E2_sum / measured_steps - E_sum * E_sum / (measured_steps * measured_steps)) / (T * T * N);
    susceptibility = (M2_sum / measured_steps - M_sum * M_sum / (measured_steps * measured_steps)) / (T * N);

    /*
    std::cout << "Average energy per spin: " << average_energy << std::endl;
    std::cout << "Average magnetisation per spin: " << average_magnetisation << std::endl;
    std::cout << "Specific heat: " << specific_heat << std::endl;
    std::cout << "Susceptibility: " << susceptibility << std::endl;
    */
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


