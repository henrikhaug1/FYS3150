#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <omp.h>
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

void write_to_file_8(std::string filename, arma::vec temperature, std::vector<double> eps, std::vector<double> mag, std::vector<double> heat_cap, std::vector<double> sus)
{
    int width = 15;  
    int prec = 8;     

    std::ofstream outfile(filename);

    outfile << std::left << std::setw(width) << "Temperature"
            << std::setw(width) << "Energy"
            << std::setw(width) << "Magnetization"
            << std::setw(width) << "Heat Capacity"
            << std::setw(width) << "Susceptibility" << "\n";

    for (size_t i = 0; i < temperature.n_elem; ++i)
    {
        outfile << std::left << std::setw(width) << std::setprecision(prec) << temperature[i]
                << std::setw(width) << std::setprecision(prec) << eps[i]
                << std::setw(width) << std::setprecision(prec) << mag[i] 
                << std::setw(width) << std::setprecision(prec) << heat_cap[i]
                << std::setw(width) << std::setprecision(prec) << sus[i] << "\n";
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

    #pragma omp parallel for
    for (size_t t = 0; t < Temp.size(); t++)
    {
        double T_local = Temp[t];

        // Vectors to store energies for ordered and unordered states
		std::vector<double> energies_ordered;
	    std::vector<double> cumulative_energies_ordered;
	    std::vector<double> energy_samples_ordered;

	    std::vector<double> energies_unordered;
	    std::vector<double> cumulative_energies_unordered;
	    std::vector<double> energy_samples_unordered;

        // Ordered initial state
        IsingModel ordered_model(L, T_local, J, true);
        ordered_model.metropolis(num_steps, energies_ordered, cumulative_energies_ordered, energy_samples_ordered);

        // Unordered initial state
        IsingModel unordered_model(L, T_local, J, false);
        unordered_model.metropolis(num_steps, energies_unordered, cumulative_energies_unordered, energy_samples_unordered);

        // Save energy data to files for plotting
        std::string filename_ordered = "energy_L" + std::to_string(L) + "_T" + std::to_string(T_local) + "_ordered.txt";
        write_to_file_energy(filename_ordered, energies_ordered, cumulative_energies_ordered, energy_samples_ordered);

        std::string filename_unordered = "energy_L" + std::to_string(L) + "_T" + std::to_string(T_local) + "_unordered.txt";
        write_to_file_energy(filename_unordered, energies_unordered, cumulative_energies_unordered, energy_samples_unordered);

    }

        // ---------- L = {40, 60, 80, 100} ----------

    std::vector<int> lattice_sizes = {40, 60, 80, 100};
    double dt = 0.01;
    arma::vec temperature = arma::regspace(2.1, dt, 2.4 + dt);
    temperature.print();

    omp_set_num_threads(4);
    #pragma omp parallel for
    for(int i = 0; i < lattice_sizes.size(); i++)
    {
        std::vector<double> av_energy;
        std::vector<double> av_magnetisation;
        std::vector<double> sp_heat;
        std::vector<double> sus;

        for (int j = 0; j < temperature.n_elem; j++)
        {    
            IsingModel model_many = IsingModel(lattice_sizes[i], temperature[j], J, false);
            std::vector<double> energies;
            std::vector<double> cumulative_energies;
            std::vector<double> energy_samples;


            model_many.metropolis(temperature.n_elem, energies, cumulative_energies, energy_samples);

            av_energy.push_back(model_many.average_energy);
            av_magnetisation.push_back(model_many.average_magnetisation);
            sp_heat.push_back(model_many.specific_heat);
            sus.push_back(model_many.susceptibility);

        }

        std::string filename = "L" + std::to_string(lattice_sizes[i]) + "_func_of_temp.txt";
        write_to_file_8(filename, temperature, av_energy, av_magnetisation, sp_heat, sus);
    }

    return 0;
}









