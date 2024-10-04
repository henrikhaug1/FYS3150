#include <iostream>
#include <armadillo>

#include "PenningTrap.hpp"

// Defining global variables 
const long double T = 9.64852558e1; // u / ((𝝁s)^2 * e)
const long double V = 9.64852558e7; // (u (𝝁m)^2) / ((𝝁s)^2 * e)


// Constructor
PenningTrap::PenningTrap(double B0_in=T, double V0_in=25*V, double d_in=500)
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

	x_vec(0) = x;
	y_vec(1) = y;
	z_vec(2) = z;


	arma::vec E = ( V0 / (2*d*d) ) * (2*z*z - x*x - y*y); //skal vi hardcode V0/d^2?

	return E;
} 

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r) //HVORFOR TAR VI INN r HER??
{
	arma::vec B = r;
	B(2) = B0;
	return B;
}  

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j) //HVORFOR TRENGER VI i
{
	Particle particle_j = particle_collection[j];
	arma::vec external_E_j = external_E_field(particle_j);
	arma::vec external_B_j = external_B_field(particle_j);

	arma::vec force_on_i_from_j = external_E_j + external_B_j;
	return force_on_i_from_j;

}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
	Particle particle_i = particle_collection[i];
	double q = particle_i.charge;

	arma::vec external_E_i = external_E_field(particle_i.position);
	arma::vec external_B_i = external_B_field(particle_i.position);
	arma::vec velocity_i = particle_i.velocity;
	arma::vec F = q * external_E_i + arma::cross(q * velocity_i, external_B_i);
	return F;
}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
	arma::vec total_force_on_i;
	for(int j = 0; j < particle_collection.n_elem; i++)
	{
		total_force_on_i += total_force_particles(j);
	}
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
	arma::vec total_force_particles;
	for(int i = 0; i < particle_collection.n_elem; i++)
	{
		total_force_particles += total_force_external(i);
		total_force_particles += total_force_particles(i);
	}
	
	return total_force_particles;
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



