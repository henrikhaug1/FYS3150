#ifndef __IsingModel_hpp__
#define __IsingModel_hpp__

#include <armadillo>

const long double k_b = 1.0; //1.380649e-23;

class IsingModel
{
    public:
    	int L;  // Lattice dimension
        double T;  // Temperature
        double J;  // Coupling constant
        arma::Mat<int> spins;  // matrix for spin configuration

    // Constructor
    IsingModel(int L_in = 10, double temp_in = 1.0, double J_in = 1.0);

    // Function that returns the total energy of the system
    double total_energy(const arma::Mat<int>& spins);

    // Function that returns the energy per spin
    double energy_per_spin();

    // Function that returns the total magnetisation of the system
    double magnetisation(const arma::Mat<int>& spins);

    // Function that returns the magnetisation per spin
    double magnetisation_per_spin();

    double partition_function();

    double probability_state();

};

#endif
