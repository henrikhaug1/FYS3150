#include <iostream>
#include "IsingModel.hpp"

int main()
{
	int L = 5;           // Lattice size (20x20)
    double T = 2.0;       // Temperature
    int num_steps = 100000; // Number of Monte Carlo steps

    IsingModel model(L, T);
    model.metropolis(num_steps);

    std::cout << "Temperature: " << T << std::endl;
    std::cout << "Energy per Spin: " << model.energy_per_spin() << std::endl;
    std::cout << "Average Magnetization per Spin: " << model.magnetisation_per_spin() << std::endl;
	std::cout << "partition_function" << model.partition_function() << std::endl;
	std::cout << "probability_state" << model.probability_state() << std::endl;


    return 0;
}
