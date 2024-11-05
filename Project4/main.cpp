#include <iostream>
#include "IsingModel.hpp"

int main()
{
	int L = 5;           // Lattice size
    double T = 1.0;       // Temperature
    int num_steps = 100; // Number of Monte Carlo steps

    IsingModel model(L, T);
    model.metropolis(num_steps);

	std::cout << "Temperature: " << T << std::endl;
	std::cout << "Average Energy per Spin: " << model.average_energy << std::endl;
	std::cout << "Average Magnetization per Spin: " << model.average_magnetisation << std::endl;
	std::cout << "Specific Heat per Spin: " << model.specific_heat << std::endl;
	std::cout << "Susceptibility per Spin: " << model.susceptibility << std::endl;

    return 0;
}
