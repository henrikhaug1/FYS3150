#include <iostream>
#include <armadillo>
#include <cmath>
#include <complex> 

#include "PenningTrap.hpp"
#include "Particle.hpp"

// Defining global variables 
const long double k_e = 1.38935333e5; // (u (𝝁m)^3) / ((𝝁s)^2 * e^2)


// Constructor
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, bool particle_interactions_in, bool time_dependent_v0_in, double f_in, double omega_v_in)
{
	B0 = B0_in;
	V0 = V0_in;
	d = d_in;
	particle_interactions = particle_interactions_in;
	time_dependent_v0 = time_dependent_v0_in;
	f = f_in;
	omega_v = omega_v_in;
}


// Add a particle to the trap
void PenningTrap::add_particle(Particle p_in)
{
	particle_collection.push_back(p_in);
}

//Add a random particle to trap:
void PenningTrap::add_random_particle(int n, int charge, double mass)
{
	arma::arma_rng::set_seed_random();
	for (int i = 0; i < n; i++){
	    arma::vec r = arma::vec(3).randn()*0.1*d;
	    arma::vec v = arma::vec(3).randn()*0.1*d;
	    particle_collection.push_back(Particle(charge, mass, r, v));
	}
}

//count amount of particles within radius d
int PenningTrap::count_particles()
{
	int count = 0;
	for(int i = 0; i < particle_collection.size(); i++)
	{
		if(norm(particle_collection[i].return_position() < d))
		{
			count +=1;
		}
	}
	return count;
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
	double x = r(0);
	double y = r(1);
	double z = r(2);


	arma::vec e_x = {2 * x, 0, 0};
	arma::vec e_y = {0, 2 * y, 0};
	arma::vec e_z = {0, 0, 2.0 * 2 * z};

	arma::vec E =  - ( V0 / (2.0*d*d) ) * (e_z - e_x - e_y);

	if(arma::norm(r) > d)
	{
		E = arma::vec(3, arma::fill::zeros);
	}

	if (time_dependent_v0)
	{
    	E = E * (1. + f*cos(omega_v*simulation_time));
    	std::cout << "f" << f << "omega_v" << omega_v << std::endl;

  	}


	return E;
}


// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
	arma::vec B = arma::vec({0, 0, B0});
	if(arma::norm(r) > d)
	{
		B = arma::vec(3, arma::fill::zeros);
	}
	return B;
}  

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j)
{
    arma::vec r_i = particle_collection[i].return_position();
    arma::vec r_j = particle_collection[j].return_position();
    double q_i = particle_collection[i].return_charge();
    double q_j = particle_collection[j].return_charge();

    arma::vec r_diff = r_i - r_j;
    double distance_squared = arma::dot(r_diff, r_diff);

    if (distance_squared == 0) return arma::vec(3, arma::fill::zeros); // Prevent division by zero

    return k_e * q_i * q_j * r_diff / distance_squared;
}


// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
	Particle particle_i = particle_collection[i];
	double q = particle_i.return_charge();

	arma::vec external_E_i = external_E_field(particle_i.return_position());
	arma::vec external_B_i = external_B_field(particle_i.return_position());
	arma::vec velocity_i = particle_i.return_velocity();

	arma::vec F = q * (external_E_i + arma::cross(velocity_i, external_B_i));
	return F;

}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
	arma::vec total_force_on_i = arma::vec(3, arma::fill::zeros);
	for(int j = 0; j < particle_collection.size(); j++)
	{
		if(j != i)
		{
			total_force_on_i += force_particle(i, j);
		}
	}

	return total_force_on_i;
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
	if(particle_interactions)
	{
		return total_force_particles(i) + total_force_external(i);
	}
	else
	{
		return total_force_external(i);
	}
}




// Evolve the system one time step (dt) using Forward Euler
void PenningTrap::evolve_forward_euler(double dt)
{	
	for(int i = 0; i < particle_collection.size(); i++)
	{
		Particle& particle_i = particle_collection[i];
		arma::vec total_force_i = total_force(i);

		arma::vec new_velocity = particle_i.return_velocity() + dt * 
								 total_force_i / particle_i.return_mass();

		arma::vec new_position = particle_i.return_position() + dt * particle_i.return_velocity();

		particle_i.set_position(new_position);
		particle_i.set_velocity(new_velocity);

	}	
}

/*
// Evolve the system one time step (dt) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(double dt)
{
    for(int i = 0; i < particle_collection.size(); i++)
    {	
        Particle& particle_i = particle_collection[i];
        arma::vec initial_position = particle_i.return_position();
        arma::vec initial_velocity = particle_i.return_velocity();
        arma::vec total_force_i = total_force(i);

        arma::vec temp_position;
        arma::vec temp_velocity;

        // k1
        arma::vec k_x1 = dt * initial_velocity;
        arma::vec k_v1 = dt * (total_force_i / particle_i.return_mass());

        // k2
        temp_position = initial_position + 0.5 * k_x1;
        temp_velocity = initial_velocity + 0.5 * k_v1;
        arma::vec total_force_k2 = total_force(i); 
        arma::vec k_x2 = dt * temp_velocity;
        arma::vec k_v2 = dt * (total_force_k2 / particle_i.return_mass());

        // k3
        temp_position = initial_position + 0.5 * k_x2;
        temp_velocity = initial_velocity + 0.5 * k_v2;
        arma::vec total_force_k3 = total_force(i); 
        arma::vec k_x3 = dt * temp_velocity;
        arma::vec k_v3 = dt * (total_force_k3 / particle_i.return_mass());

        // k4
        temp_position = initial_position + k_x3;
        temp_velocity = initial_velocity + k_v3;
        arma::vec total_force_k4 = total_force(i); 
        arma::vec k_x4 = dt * temp_velocity;
        arma::vec k_v4 = dt * (total_force_k4 / particle_i.return_mass());

        // Final updates
        arma::vec x_ip1 = initial_position + (1.0 / 6.0) * (k_x1 + 2 * k_x2 + 2 * k_x3 + k_x4);
        arma::vec v_ip1 = initial_velocity + (1.0 / 6.0) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4);

        particle_i.set_position(x_ip1);
        particle_i.set_velocity(v_ip1);

        simulation_time += dt;
    }
}
*/
void PenningTrap::evolve_RK4(double dt)
{
    for(int i = 0; i < particle_collection.size(); i++)
    {	
        Particle& particle_i = particle_collection[i];
        arma::vec initial_position = particle_i.return_position();
        arma::vec initial_velocity = particle_i.return_velocity();
        arma::vec total_force_i = total_force(i);

        arma::vec temp_position;
        arma::vec temp_velocity;

        // k1
        arma::vec k_x1 = dt * initial_velocity;
        arma::vec k_v1 = dt * (total_force_i / particle_i.return_mass());

        // k2
        temp_position = initial_position + 0.5 * k_x1;
        temp_velocity = initial_velocity + 0.5 * k_v1;
        particle_i.set_position(temp_position);
        particle_i.set_velocity(temp_velocity);
        arma::vec total_force_k2 = total_force(i); 
        arma::vec k_x2 = dt * temp_velocity;
        arma::vec k_v2 = dt * (total_force_k2 / particle_i.return_mass());

        // k3
        temp_position = initial_position + 0.5 * k_x2;
        temp_velocity = initial_velocity + 0.5 * k_v2;
        particle_i.set_position(temp_position);
        particle_i.set_velocity(temp_velocity);
        arma::vec total_force_k3 = total_force(i); 
        arma::vec k_x3 = dt * temp_velocity;
        arma::vec k_v3 = dt * (total_force_k3 / particle_i.return_mass());

        // k4
        temp_position = initial_position + k_x3;
        temp_velocity = initial_velocity + k_v3;
        particle_i.set_position(temp_position);
        particle_i.set_velocity(temp_velocity);
        arma::vec total_force_k4 = total_force(i); 
        arma::vec k_x4 = dt * temp_velocity;
        arma::vec k_v4 = dt * (total_force_k4 / particle_i.return_mass());

        // Final updates
        arma::vec x_ip1 = initial_position + (1.0 / 6.0) * (k_x1 + 2 * k_x2 + 2 * k_x3 + k_x4);
        arma::vec v_ip1 = initial_velocity + (1.0 / 6.0) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4);

        particle_i.set_position(x_ip1);
        particle_i.set_velocity(v_ip1);

        simulation_time += dt;
    }
}


// Spesific analytical solutution
void PenningTrap::specific_analytical_solution(Particle particle, arma::vec time, arma::vec& x, arma::vec& y, arma::vec& z)
{
	double q = particle.return_charge();
    double m = particle.return_mass();

	double x0 = particle.return_position()(0);
    double v0 = particle.return_velocity()(1);
	double z0 = particle.return_position()(2);

    double phi_p = 0.0;
    double phi_m = 0.0;

	double omega_0 = (q * B0) / m;
	double omega_z_squared = (2 * q * V0) / (m * d * d);
	double omega_z = std::sqrt(omega_z_squared);

	double omega_p = (omega_0 + std::sqrt(omega_0 * omega_0 - 2.0 * omega_z_squared)) / 2.0;
    double omega_m = (omega_0 - std::sqrt(omega_0 * omega_0 - 2.0 * omega_z_squared)) / 2.0;

    double A_p = (v0 + omega_m * x0) / (omega_m - omega_p);
    double A_m = -(v0 + omega_p * x0) / (omega_m - omega_p);


    std::complex<double> I(0.0, 1.0);
    // Loop over time and calculate the real part in x[t] and imaginary part in y[t]
    for (int t = 0; t < time.n_elem; t++)
    {
        std::complex<double> f_t = A_p * std::exp(-I * (omega_p * time(t) + phi_p)) +
                                   A_m * std::exp(-I * (omega_m * time(t) + phi_m));

        // Extract the real and imaginary parts
        x[t] = std::real(f_t);  // Real part goes to x
        y[t] = std::imag(f_t);  // Imaginary part goes to y
        z[t] = z0 * cos(omega_z * time(t));
    }
}


















