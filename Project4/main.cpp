#include <iostream>
#include "IsingModel.hpp"

int main()
{
    int L = 2;        // 2x2 lattice
    double T = 1.0;   // Dimensionless temperature
    double J = 1.0;   // Coupling constant set to 1.0

    IsingModel model(L, T, J);

    double E = model.total_energy(model.spins);
    std::cout << "tot energy = " << E << std::endl;

    std::cout << 1/(k_b * T) << std::endl;


    // Print partition function
    double Z = model.partition_function();
    std::cout << "Partition function Z = " << Z << std::endl;

    // Print probability of the current configuration
    double prob = model.probability_state();
    std::cout << "Probability of current configuration = " << prob << std::endl;

    return 0;
}
