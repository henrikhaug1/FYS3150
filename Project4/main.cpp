#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "IsingModel.hpp"

void write_to_file_energy(std::string filename, std::vector<double> energies, std::vector<double> cumulative_energies, std::vector<double> energy_samples)
{
    int width = 10;
    int prec = 15;

    std::ofstream outfile(filename);
    for (size_t i = 0; i < energies.size(); ++i)
    {
        outfile << i << std::setw(width) << energies[i] << std::setw(width) << cumulative_energies[i] << std::setw(width) << energy_samples[i] << "\n";
    }
    outfile.close();

}



int main()
{
    //---------- L = 2 ----------
    int L = 2;           // Lattice size
    double T = 1;      // Temperature
    int num_steps = 10000;  // Number of Monte Carlo cycles
    double J = 1.0;

    std::vector<double> energies_ordered;
    std::vector<double> cumulative_energies_ordered;
    std::vector<double> energy_samples_ordered;

    std::vector<double> energies_unordered;
    std::vector<double> cumulative_energies_unordered;
    std::vector<double> energy_samples_unordered;

    // Ordered initial state
    IsingModel model_ordered(L, T, J, true); // 'true' for ordered state
    model_ordered.spins.print();
    model_ordered.metropolis(num_steps, energies_ordered, cumulative_energies_ordered, energies_ordered);

    std::cout << "Temperature: " << T << std::endl;
    std::cout << "Average Energy per Spin (Ordered): " << model_ordered.average_energy << std::endl;
    std::cout << "Average Magnetization per Spin (Ordered): " << model_ordered.average_magnetisation << std::endl;
    std::cout << "Specific Heat per Spin (Ordered): " << model_ordered.specific_heat << std::endl;
    std::cout << "Susceptibility per Spin (Ordered): " << model_ordered.susceptibility << std::endl;
    std::cout << "\n";

    model_ordered.spins.print();

    // Unordered initial state
    IsingModel model_unordered(L, T, J, false); // 'false' for unordered state
    model_unordered.metropolis(num_steps, energies_unordered, cumulative_energies_unordered, energy_samples_unordered);

    std::cout << "Average Energy per Spin (Unordered): " << model_unordered.average_energy << std::endl;
    std::cout << "Average Magnetization per Spin (Unordered): " << model_unordered.average_magnetisation << std::endl;
    std::cout << "Specific Heat per Spin (Unordered): " << model_unordered.specific_heat << std::endl;
    std::cout << "Susceptibility per Spin (Unordered): " << model_unordered.susceptibility << std::endl;


    //---------- L = 20 ----------
    L = 20; // Update lattice size
    num_steps = 10000; // Adjust the number of steps as needed
    std::vector<double> Temp = {1.0, 2.4}; // Temperatures to simulate
    int width = 10;
    int prec = 15;

    for (size_t t = 0; t < Temp.size(); t++)
    {
        T = Temp[t];

        // Vectors to store energies for ordered and unordered states
        energies_ordered.clear();
        cumulative_energies_ordered.clear();
        energy_samples_ordered.clear();

        energies_unordered.clear();
        cumulative_energies_unordered.clear();
        energy_samples_unordered.clear();

        // Ordered initial state
        IsingModel ordered_model(L, T, J, true);
        ordered_model.metropolis(num_steps, energies_ordered, cumulative_energies_ordered, energy_samples_ordered);

        // Unordered initial state
        IsingModel unordered_model(L, T, J, false);
        unordered_model.metropolis(num_steps, energies_unordered, cumulative_energies_unordered, energy_samples_unordered);

        // Save energy data to files for plotting
        std::string filename_ordered = "energy_L" + std::to_string(L) + "_T" + std::to_string(T) + "_ordered.txt";
        write_to_file_energy(filename_ordered, energies_ordered, cumulative_energies_ordered, energy_samples_ordered);

        std::string filename_unordered = "energy_L" + std::to_string(L) + "_T" + std::to_string(T) + "_unordered.txt";
        write_to_file_energy(filename_unordered, energies_unordered, cumulative_energies_unordered, energy_samples_unordered);



    return 0;
}


