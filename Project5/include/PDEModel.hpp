#ifndef __PDEModel_hpp__
#define __PDEModel_hpp__

#include <iostream>
#include <armadillo>


class PDEModel
{
    private:
        double dt, dx, dy;
        


    // Constructor 
    PDEModel(double dt, double dx, double dy);

    // Initial conditions u_ij^0
    void initial_state();

    void normalised_initial_state();

    void initial_boundary_conditions();


};

#endif