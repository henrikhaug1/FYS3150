#ifndef __PenningTrap_hpp__
#define __PenningTrap_hpp__

#include "Particle.hpp"

const long double T = 9.64852558e1; // u / ((𝝁s)^2 * e)
const long double V = 2.41e6; // (u (𝝁m)^2) / ((𝝁s)^2 * e)

class PenningTrap
{
	public:
		double B0;
		double V0;
		double d;
		std::vector<Particle> particle_collection;
		bool particle_interactions;
		bool time_dependent_v0;


	// Constructor
	PenningTrap(double B0_in=T, double V0_in=V, double d_in=500, bool particle_interactions_in = false, bool time_dependent_v0_in = false);

	// Add a particle to the trap
	void add_particle(Particle p_in);

	// External electric field at point r=(x,y,z)
	arma::vec external_E_field(arma::vec r);  

	// External magnetic field at point r=(x,y,z)
	arma::vec external_B_field(arma::vec r);  

	// Force on particle_i from particle_j
	arma::vec force_particle(int i, int j);

	// The total force on particle_i from the external fields
	arma::vec total_force_external(int i);

	// The total force on particle_i from the other particles
	arma::vec total_force_particles(int i);

	// The total force on particle_i from both external fields and other particles
	arma::vec total_force(int i);

	// Evolve the system one time step (dt) using Forward Euler
	void evolve_forward_euler(double dt);

	// Evolve the system one time step (dt) using Runge-Kutta 4th order
	void evolve_RK4(double dt);

	arma::vec specific_analytical_z(Particle particle, arma::vec time);

	void specific_analytical_xy(Particle particle, arma::vec time, arma::vec& x, arma::vec& y);

};

#endif