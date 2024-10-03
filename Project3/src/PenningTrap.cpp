#include <iostream>
#include <armadillo>

#include "PenningTrap.hpp"

// Constructor
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in)
{
	B0 = B0_in;
	V0 = V0_in;
	d = d_in; 
}


// Add a particle to the trap
void PenningTrap::add_particle(Particle p_in)
{
	particle_collection.push_back(p_in);
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
	double x = r(0);
	double y = r(1);
	double z = r(2);

	arma::vec x_vec = arma::vec(3).fill(0);
	arma::vec y_vec = arma::vec(3).fill(0);
	arma::vec z_vec = arma::vec(3).fill(0);

	x_vec(0), y_vec(1), z_vec(2) = x, y, z;

	arma::vec E = ( V0 / (2*d*d) ) * (2*z*z - x*x - y*y);

	return E;
} 

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
	// ...
}  

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j)
{
	// ...
}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
	// ...
}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
	// ...
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
	// ...
}

// Evolve the system one time step (dt) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(double dt)
{
	// ...
}

// Evolve the system one time step (dt) using Forward Euler
void PenningTrap::volve_forward_Euler(double dt)
{
	// ...
}



