#include <iostream>
#include "IsingModel.hpp"

IsingModel::IsingModel(int L_in, double temp_in, double J_in)
    : L(L_in), T(temp_in), J(J_in), spins(L_in, L_in)
{
	//initialize spins
	spins.imbue([]() { return arma::randi<int>(arma::distr_param(0, 1)) * 2 - 1; });

}

double IsingModel::total_energy(const arma::Mat<int>& spins) {
    double E = 0.0;

    for (int k = 0; k < L; k++) {
        for (int l = 0; l < L; l++) {
            int spin = spins(k, l);
            int neighbor_sum = spins((k + 1) % L, l) +  // Right neighbor
                               spins((k - 1 + L) % L, l) +  // Left neighbor
                               spins(k, (l + 1) % L) +  // Down neighbor
                               spins(k, (l - 1 + L) % L);  // Up neighbor

            E -= J * spin * neighbor_sum;
        }
    }

    return E / 2.0;
}

double IsingModel::energy_per_spin()
{
	return total_energy(spins) / (L * L);
}

double IsingModel::magnetisation(const arma::Mat<int>& spins)
{
	int sum = 0;
	for (int i = 0; i < L; i++)
	{
		for(int j = 0; j < L; j++)
		{
			sum += spins(i, j);
		}
		
	}
	return sum;
}

double IsingModel::magnetisation_per_spin()
{
	return magnetisation(spins) / (L * L);
}


double IsingModel::partition_function()
{
    double Z = 0.0;
    int num_states = std::pow(2, L * L);
    arma::Mat<int> spin_config = spins;
    double beta = 1.0 / T; // Since k_b = 1.0

    for (int state = 0; state < num_states; state++)
    {
        // Set spin configuration for each possible state
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < L; j++)
            {
                spin_config(i, j) = ((state >> (i * L + j)) & 1) ? 1 : -1;
            }
        }
        
        // Calculate energy for the current configuration
        double E = total_energy(spin_config);
        Z += std::exp(-beta * E);
    }
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
