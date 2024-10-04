#include <iostream>
#include <armadillo>

#include "PenningTrap.hpp"
#include "Particle.hpp"

// Defining global variables 
const long double k_e = 1.38935333e5; // (u (𝝁m)^3) / ((𝝁s)^2 * e^2)


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

	x_vec(0) = x;
	y_vec(1) = y;
	z_vec(2) = z;


	arma::vec E = ( V0 / (2.0*d*d) ) * (2.0*z_vec*z_vec - x_vec*x_vec - y_vec*y_vec);

	return E;
} 

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
	arma::vec B = arma::vec({0, 0, B0});
	return B;
}  

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j)
{
	arma::vec r_i = particle_collection[i].return_position();
	arma::vec r_j = particle_collection[j].return_position();
	arma::vec distance = r_i - r_j;

	double q_i = particle_collection[i].return_charge();
	double q_j = particle_collection[j].return_charge();

	arma::vec E = external_E_field(distance);

	
	arma::vec force_ij = k_e * (q_i * q_j) * (r_i - r_j) / distance * distance * distance;

	return force_ij;
}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
	Particle particle_i = particle_collection[i];
	double q = particle_i.return_charge();

	arma::vec external_E_i = external_E_field(particle_i.return_position());
	arma::vec external_B_i = external_B_field(particle_i.return_position());
	arma::vec velocity_i = particle_i.return_velocity();
	arma::vec F = q * external_E_i + arma::cross(q * velocity_i, external_B_i);
	return F;
}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
	arma::vec total_force_on_i;
	for(int j = 0; j < particle_collection.size(); j++)
	{
		total_force_on_i += force_particle(i, j);
	}

	return total_force_on_i;
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
	arma::vec total_force;
	total_force = total_force_particles(i) + total_force_external(i);

	return total_force;
}

/*
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

*/

