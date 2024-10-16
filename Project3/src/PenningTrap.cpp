#include <iostream>
#include <armadillo>
#include <cmath>
#include <complex> 

#include "PenningTrap.hpp"
#include "Particle.hpp"

// Defining global variables 
const long double k_e = 1.38935333e5; // (u (𝝁m)^3) / ((𝝁s)^2 * e^2)


// Constructor
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, bool particle_interactions_in, bool time_dependent_v0_in)
{
	B0 = B0_in;
	V0 = V0_in;
	d = d_in;
	particle_interactions = particle_interactions_in;
	time_dependent_v0 = time_dependent_v0_in;
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


	arma::vec e_x = {x * x, 0, 0};
	arma::vec e_y = {0, y * y, 0};
	arma::vec e_z = {0, 0, 2.0 * z * z};

	arma::vec E = ( V0 / (2.0*d*d) ) * (e_z - e_x - e_y);

	if(arma::norm(r) > d)
	{
		E = arma::vec(3, arma::fill::zeros);
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
	
	arma::vec force_ij = k_e * q_i*q_j / ( (r_i-r_j)%(r_i-r_j) ) % ( (r_i-r_j)/abs(r_i-r_j) );
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

	arma::vec F = q * (external_E_i + arma::cross(velocity_i, external_B_i));
	return F;

}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
	arma::vec total_force_on_i = arma::vec(3);
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
		arma::vec new_position = particle_i.return_position() + dt * new_velocity;

		particle_i.set_position(new_position);
		particle_i.set_velocity(new_velocity);
		

	}	
}


// Evolve the system one time step (dt) using Runge-Kutta 4th order

void PenningTrap::evolve_RK4(double dt)
{
    for(int i = 0; i < particle_collection.size(); i++)
    {
        Particle& particle_i = particle_collection[i];
        arma::vec initial_position = particle_i.return_position();
        arma::vec initial_velocity = particle_i.return_velocity();
        arma::vec total_force_i = total_force(i);

        // k1
        arma::vec k_x1 = dt * initial_velocity;
        arma::vec k_v1 = dt * (total_force_i / particle_i.return_mass());

        // k2
        arma::vec temp_position = initial_position + 0.5 * k_x1;
        arma::vec temp_velocity = initial_velocity + 0.5 * k_v1;
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
    }
}



arma::vec PenningTrap::specific_analytical_z(Particle particle, arma::vec time)
{
	arma::vec z_t = arma::vec(time.n_elem);

	double z0 = particle.return_position()(2);
	double omega_z = sqrt((2 * particle.return_charge() * V0) / particle.return_mass() * d * d);

	for(int t = 0; t < time.n_elem; t++)
	{
		z_t[t] = z0 * cos(omega_z * time(t));
	}

	return z_t;
}

void PenningTrap::specific_analytical_xy(Particle particle, arma::vec time, arma::vec& x, arma::vec& y)
{
    arma::vec f_t = arma::vec(time.n_elem);

    double x0 = particle.return_position()(0);
    double v0 = particle.return_velocity()(1);

    std::cout << x0 << " " << v0 << "\n";

    std::complex<double> I(0.0, 1.0);  // Imaginary unit

    double charge = particle.return_charge();
    double mass = particle.return_mass();

    double omega_0 = (charge * B0) / mass;
    std::cout << "charge: " << charge << "\n"
              << "B0: " << B0 << "\n"
              << "mass:" << mass << std::endl;

    // Omega_z squared (could be negative inside sqrt, hence handled with complex)
    double omega_z_2 = (2 * charge * V0) / (mass * d * d);

    // Calculate omega_p and omega_m as complex numbers to avoid negative square root
    std::complex<double> omega_p = (omega_0 + std::sqrt(std::complex<double>(omega_0 * omega_0 - 2.0 * omega_z_2))) / 2.0;
    std::complex<double> omega_m = (omega_0 - std::sqrt(std::complex<double>(omega_0 * omega_0 - 2.0 * omega_z_2))) / 2.0;

    // Set the phases to zero (or adjust based on need)
    double phi_p = 0.0;
    double phi_m = 0.0;

    // Calculate coefficients A_p and A_m
    std::complex<double> A_p = (v0 + omega_m * x0) / (omega_m - omega_p);
    std::complex<double> A_m = -(v0 + omega_p * x0) / (omega_m - omega_p);

    std::cout << "omega_0: " << omega_0 << "\n";
    std::cout << "omega_z_2: " << omega_z_2 << "\n";
    std::cout << "omega_p: " << omega_p << "\n";
    std::cout << "omega_m: " << omega_m << "\n";
    std::cout << "A_p: " << A_p << "\n";
    std::cout << "A_m: " << A_m << "\n";

    // Loop over time and calculate the real part in x[t] and imaginary part in y[t]
    for (int t = 0; t < time.n_elem; t++)
    {
        // Compute the complex f(t) based on the given formula
        std::complex<double> f_t = A_p * std::exp(-I * (omega_p * time(t) + phi_p)) +
                                   A_m * std::exp(-I * (omega_m * time(t) + phi_m));

        // Extract the real and imaginary parts
        x[t] = std::real(f_t);  // Real part goes to x
        y[t] = std::imag(f_t);  // Imaginary part goes to y
    }
}

void PenningTrap::trajectories(Particle particle, arma::vec time, arma::vec& vec1, arma::vec& vec2)
{

	for(int t = 0; t < time.n_elem; t++)
	{
		vec1[t] = particle.return_position()(0);
		vec2[t] = particle.return_position()(0);
	}

}

















