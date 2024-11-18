#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "IsingModel.hpp"

void write_to_file_energy(std::string filename, std::vector<double> energies, std::vector<double> cumulative_energies, std::vector<double> magnetisation)
{
    int width = 15;
    int prec = 15;

    std::ofstream outfile(filename);
    for (size_t i = 0; i < energies.size(); ++i)
    {
        outfile << i << std::setw(width) << energies[i] << std::setw(width) << cumulative_energies[i] << std::setw(width) << magnetisation[i] << "\n";
    }
    outfile.close();

}


void write_to_file_8(std::string filename, arma::vec temperature, std::vector<double> eps, std::vector<double> eps2, std::vector<double> mag, std::vector<double> mag2, std::vector<double> heat_cap, std::vector<double> sus)
{
    int width = 15;  
    int prec = 8;     

    std::ofstream outfile(filename);

    outfile << std::left << std::setw(width) << "Temperature"
            << std::setw(width) << "Energy"
            << std::setw(width) << "Energy2"
            << std::setw(width) << "Magnetization"
            << std::setw(width) << "Magnetization2"
            << std::setw(width) << "Heat Capacity"
            << std::setw(width) << "Susceptibility" << "\n";

    for (size_t i = 0; i < temperature.n_elem; ++i)
    {
        outfile << std::left << std::setw(width) << std::setprecision(prec) << temperature[i]
                << std::setw(width) << std::setprecision(prec) << eps[i]
                << std::setw(width) << std::setprecision(prec) << eps2[i]
                << std::setw(width) << std::setprecision(prec) << mag[i] 
                << std::setw(width) << std::setprecision(prec) << mag2[i]
                << std::setw(width) << std::setprecision(prec) << heat_cap[i]
                << std::setw(width) << std::setprecision(prec) << sus[i] << "\n";
    }
    outfile.close();
}



double critical_temperature(int lattice_sizes)
{
    double T_c_inf = 2.269;
    double L_inverse = 1. / lattice_sizes;
    double a = 1;
    double T_c = a * L_inverse + T_c_inf;

    return T_c;
}



int main()
{
    
    int mc_cycles = 10000;
    double dt = 0.01;
    double J = 1.0;




    // --------------- Problem 2 (L = 2) ---------------
    std::vector<double> energies_ordered;
    std::vector<double> cumulative_energies_ordered;
    std::vector<double> magnetisations_ordered;

    std::vector<double> energies_unordered;
    std::vector<double> cumulative_energies_unordered;
    std::vector<double> magnetisations_unordered;


    // Ordered case 
    IsingModel L2_T1_ordered(2, 1, J, true);
    L2_T1_ordered.metropolis(mc_cycles, energies_ordered, cumulative_energies_ordered, magnetisations_ordered);

    std::cout << "---------- ORDERED ----------" << std::endl;
    std::cout << "Average Energy per Spin:          " << L2_T1_ordered.average_energy << std::endl;
    std::cout << "Average Magnetization per Spin:   " << L2_T1_ordered.average_magnetisation << std::endl;
    std::cout << "Specific Heat per Spin:           " << L2_T1_ordered.specific_heat << std::endl;
    std::cout << "Susceptibility per Spin:          " << L2_T1_ordered.susceptibility << std::endl;
    std::cout << "\n";
    std::cout << "\n";

    // Unordered case
    IsingModel L2_T1_unordered(2, 1, J, false);
    L2_T1_unordered.metropolis(mc_cycles, energies_unordered, cumulative_energies_unordered, magnetisations_unordered);

    std::cout << "---------- UNORDERED ----------" << std::endl;
    std::cout << "Average Energy per Spin:          " << L2_T1_unordered.average_energy << std::endl;
    std::cout << "Average Magnetization per Spin:   " << L2_T1_unordered.average_magnetisation << std::endl;
    std::cout << "Specific Heat per Spin:           " << L2_T1_unordered.specific_heat << std::endl;
    std::cout << "Susceptibility per Spin:          " << L2_T1_unordered.susceptibility << std::endl;







    // --------------- Problem 4 (L = 2) ---------------
    std::vector<double> av_energy;
    std::vector<double> av_energy2;
    std::vector<double> av_magnetisation;
    std::vector<double> av_magnetisation2;
    std::vector<double> sp_heat;
    std::vector<double> sus;

    arma::vec temperatures4 = arma::regspace(2.1, dt, 2.4 + dt);

    for (int i = 0; i < temperatures4.n_elem; i++)
    {    
        IsingModel model_many(2, temperatures4[i], J, false);

        std::vector<double> energies;
        std::vector<double> cumulative_energies;
        std::vector<double> energy_samples;
        std::vector<double> magnetisations;


        model_many.metropolis(mc_cycles, energies, cumulative_energies, magnetisations);

        av_energy.push_back(model_many.average_energy);
        av_energy2.push_back(model_many.average_energy2);
        av_magnetisation.push_back(model_many.average_magnetisation);
        av_magnetisation2.push_back(model_many.average_magnetisation2);
        sp_heat.push_back(model_many.specific_heat);
        sus.push_back(model_many.susceptibility);
    }
    
    std::string filename = "L" + std::to_string(2) + "_func_of_temp.txt";
    write_to_file_8(filename, temperatures4, av_energy, av_energy2, av_magnetisation, av_magnetisation2, sp_heat, sus);





    
    // --------------- Problem 5 (L = 20) ---------------
    std::vector<double> temperatures5 = {1.0, 2.4}; // Temperatures to simulate
    for (size_t t = 0; t < temperatures5.size(); t++)
    {
        double T = temperatures5[t];

        // Vectors to store energies for ordered and unordered states
        std::vector<double> energies_ordered;
        std::vector<double> cumulative_energies_ordered;
        std::vector<double> magnetisations_ordered;

        std::vector<double> energies_unordered;
        std::vector<double> cumulative_energies_unordered;
        std::vector<double> magnetisations_unordered;

        // Ordered initial state
        IsingModel ordered_model(20, T, J, true);
        ordered_model.metropolis(mc_cycles, energies_ordered, cumulative_energies_ordered, magnetisations_ordered);

        // Unordered initial state
        IsingModel unordered_model(20, T, J, false);
        unordered_model.metropolis(mc_cycles, energies_unordered, cumulative_energies_unordered, magnetisations_unordered);

        // Save energy data to files for plotting
        std::string filename_ordered = "energy_L" + std::to_string(20) + "_T" + std::to_string(T) + "_ordered.txt";
        write_to_file_energy(filename_ordered, energies_ordered, cumulative_energies_ordered, magnetisations_ordered);

        std::string filename_unordered = "energy_L" + std::to_string(20) + "_T" + std::to_string(T) + "_unordered.txt";
        write_to_file_energy(filename_unordered, energies_unordered, cumulative_energies_unordered, magnetisations_unordered);
    
    }
    




    /* 
    // --------------- Problem 8 (L = {40, 60, 80, 100}) ---------------
    std::vector<int> lattice_sizes = {40, 60, 80, 100};

    arma::vec temperatures8 = arma::regspace(2.1, dt, 2.4 + dt);

    for(int i = 0; i < lattice_sizes.size(); i++)
    {
        std::cout << "Starting L=" << lattice_sizes[i] << std::endl;
        std::vector<double> av_energy;
        std::vector<double> av_energy2;
        std::vector<double> av_magnetisation;
        std::vector<double> av_magnetisation2;
        std::vector<double> sp_heat;
        std::vector<double> sus;

        for (int j = 0; j < temperatures8.n_elem; j++)
        {    
            IsingModel model_many(lattice_sizes[i], temperatures8[j], J, false);
            std::vector<double> energies;
            std::vector<double> cumulative_energies;
            std::vector<double> magnetisations;

            model_many.metropolis(mc_cycles, energies, cumulative_energies, magnetisations);

            av_energy.push_back(model_many.average_energy);
            av_energy2.push_back(model_many.average_energy2);
            av_magnetisation.push_back(model_many.average_magnetisation);
            av_magnetisation2.push_back(model_many.average_magnetisation2);
            sp_heat.push_back(model_many.specific_heat);
            sus.push_back(model_many.susceptibility);

        }

        std::string filename = "L" + std::to_string(lattice_sizes[i]) + "_func_of_temp.txt";
        write_to_file_8(filename, temperatures8, av_energy, av_energy2, av_magnetisation, av_magnetisation2, sp_heat, sus);
    }
    */
    

    return 0;
}

