#ifndef __IsingModel_hpp__
#define __IsingModel_hpp__

#include <armadillo>


class IsingModel
{
    public:
    	int L;  // Lattice dimension
        double T;  // Temperature
        double J;  // Coupling constant
        arma::Mat<int> spins;  // matrix for spin configuration

    //constructor
    IsingModel(int L_in = 10, double temp_in = 1.0, double J_in = 1.0);

    //function that returns the total energy of the system
    double total_energy(const arma::Mat<int>& spins);

};

#endif
