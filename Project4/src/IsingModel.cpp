#include <iostream>
#include "IsingModel.hpp"

IsingModel::IsingModel(int L_in, double temp_in, double J_in)
    : L(L_in), T(temp_in), J(J_in), spins(L_in, L_in)
{
	//initialize spins
	spins.imbue([]() { return arma::randi<int>(arma::distr_param(0, 1)) * 2 - 1; });

}

double IsingModel::total_energy(const arma::Mat<int>& spins) {
    double sum = 0.0;

    for (int k = 0; k < L; k++) {
        for (int l = 0; l < L; l++) {
            int spin = spins(k, l);
            int neighbor_sum = spins((k + 1) % L, l) +  // Right neighbor
                               spins((k - 1 + L) % L, l) +  // Left neighbor
                               spins(k, (l + 1) % L) +  // Down neighbor
                               spins(k, (l - 1 + L) % L);  // Up neighbor

            sum += spin * neighbor_sum;
        }
    }

    return -0.5 * J * sum;
}
