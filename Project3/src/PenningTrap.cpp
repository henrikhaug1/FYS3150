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
		if(arma::norm(particle_collection[i].return_position()) < d)
		{
			count +=1;
		}
	}
	return count;
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
    if (time_dependent_v0)
    {
        //std::cout << time << std::endl;
        double V = V0*(1+f*cos(omega_v*simulation_time));
        return V/(d*d) * arma::vec(" 1 1 -2") % r;
    }
    else{
        return V0/(d*d) * arma::vec(" 1 1 -2") % r;
    }
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
	double distance = std::sqrt(distance_squared);

    if (distance_squared == 0) return arma::vec(3, arma::fill::zeros);
	
    return k_e * q_i * q_j * r_diff / (distance_squared * distance);
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

		arma::vec new_velocity = particle_i.return_velocity() + dt * total_force(i) / particle_i.return_mass();
		arma::vec new_position = particle_i.return_position() + dt * particle_i.return_velocity();

		particle_i.set_position(new_position);
		particle_i.set_velocity(new_velocity);

	}	
}

// void PenningTrap::evolve_RK4(double dt)
// {
// 	n = particle_collection.size() //Amount of particles
// 	arma::vec initial_position(n);
// 	arma::vec initial_velocity(n);

// 	arma::vec position1(n);
// 	arma::vec velocity1(n);
// 	arma::vec position2(n);
// 	arma::vec velocity2(n);
// 	arma::vec position3(n);
// 	arma::vec velocity3(n);
// 	arma::vec position4(n);
// 	arma::vec velocity4(n);

// 	arma::vec k_r1(n);
// 	arma::vec k_r2(n);
// 	arma::vec k_r3(n);
// 	arma::vec k_r4(n);

// 	arma::vec k_v1(n);
// 	arma::vec k_v2(n);
// 	arma::vec k_v3(n);
// 	arma::vec k_v4(n);

// 	arma::vec total_force_k1(n);
// 	arma::vec total_force_k2(n);
// 	arma::vec total_force_k3(n);
// 	arma::vec total_force_k4(n);
	
//     for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		Particle& particle_i = particle_collection[i];
// 		const arma::vec initial_position(i) = particle_i.return_position();   //Finds their initial positions
// 		const arma::vec initial_velocity(i) = particle_i.return_velocity();

//         // k1
// 		total_force_k1(i) = total_force(i);			//Calculates k1 for all particles
// 		k_r1(i) = dt * initial_velocity(i);
// 		k_v1(i) = dt * (total_force_k1(i) / particle_i.return_mass());
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)  //Loops over all the particles
// 	{
// 		position1(i) = initial_position(i) + 0.5 * k_r1(i);		//Calculates their new positions using k1
// 		velocity1(i) = initial_velocity(i) + 0.5 * k_v1(i);

// 		particle_i.set_position(position1(i));
// 		particle_i.set_velocity(velocity1(i)); 
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		// k2
// 		total_force_k2(i) = total_force(i);  
// 		k_r2(i) = dt * initial_velocity(i);
// 		k_v2(i) = dt * (total_force_k2(i) / particle_i.return_mass());  // Use total_force_k2
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		position2(i) = initial_position(i) + 0.5 * k_r2(i);
// 		velocity2(i) = initial_velocity(i) + 0.5 * k_v2(i);

// 		particle_i.set_position(position2(i));
// 		particle_i.set_velocity(velocity2(i));
// 	}
// 		// k3
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		total_force_k3(i) = total_force(i);
// 		k_r3(i) = dt * initial_velocity(i);  
// 		k_v3(i) = dt * (total_force_k3(i) / particle_i.return_mass());
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		position3(i) = initial_position(i) + k_r3(i);
// 		velocity3(i) = initial_velocity(i) + k_v3(i);

// 		particle_i.set_position(position3(i));
// 		particle_i.set_velocity(velocity3(i));
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {	
// 		total_force_k4(i) = total_force(i); 
// 		k_r4(i) = dt * velocity4(i);
// 		k_v4(i) = dt * (total_force_k4(i) / particle_i.return_mass());
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {
// 		position4(i) = initial_position(i) + k_r4(i);
// 		velocity4(i) = initial_velocity(i) + k_v4(i);

// 		particle_i.set_position(position4(i));
// 		particle_i.set_velocity(velocity4(i));		
// 	}
// 	for(int i = 0; i < particle_collection.size(); i++)	//Loops over all particles
//     {
//         // Final updates
//         arma::vec r_ip1 = initial_position + (1.0 / 6.0) * (k_r1 + 2 * k_r2 + 2 * k_r3 + k_r4);
//         arma::vec v_ip1 = initial_velocity + (1.0 / 6.0) * (k_v1 + 2 * k_v2 + 2 * k_v3 + k_v4);

//         particle_i.set_position(r_ip1);
//         particle_i.set_velocity(v_ip1);

//         simulation_time += dt;
//     }
// }
void PenningTrap::evolve_RK4(double dt)
{
    int n = particle_collection.size(); // Amount of particles
    
    arma::mat initial_positions(3, n);  // Assuming 3D positions
    arma::mat initial_velocities(3, n); // Assuming 3D velocities

    arma::mat k_r1(3, n);
    arma::mat k_r2(3, n);
    arma::mat k_r3(3, n);
    arma::mat k_r4(3, n);

    arma::mat k_v1(3, n);
    arma::mat k_v2(3, n);
    arma::mat k_v3(3, n);
    arma::mat k_v4(3, n);

    arma::mat total_force_k1(3, n);
    arma::mat total_force_k2(3, n);
    arma::mat total_force_k3(3, n);
    arma::mat total_force_k4(3, n);
    
    for(int i = 0; i < n; i++) { // Initial positions and velocities
        Particle& particle_i = particle_collection[i];
        initial_positions.col(i) = particle_i.return_position();
        initial_velocities.col(i) = particle_i.return_velocity();
    }

    // k1
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        total_force_k1.col(i) = total_force(i); // Calculates k1 for all particles
        k_r1.col(i) = dt * initial_velocities.col(i);
        k_v1.col(i) = dt * (total_force_k1.col(i) / particle_i.return_mass());
    }

    // k2
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        arma::vec position1 = initial_positions.col(i) + 0.5 * k_r1.col(i);
        arma::vec velocity1 = initial_velocities.col(i) + 0.5 * k_v1.col(i);

        particle_i.set_position(position1);
        particle_i.set_velocity(velocity1);
    }

    // Evaluate force again after intermediate state update
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        total_force_k2.col(i) = total_force(i);
        k_r2.col(i) = dt * (initial_velocities.col(i) + 0.5 * k_v1.col(i));
        k_v2.col(i) = dt * (total_force_k2.col(i) / particle_i.return_mass());
    }
  
    // k3
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        arma::vec position2 = initial_positions.col(i) + 0.5 * k_r2.col(i);
        arma::vec velocity2 = initial_velocities.col(i) + 0.5 * k_v2.col(i);

        particle_i.set_position(position2);
        particle_i.set_velocity(velocity2);
    }

    // Evaluate force again after intermediate state update
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        total_force_k3.col(i) = total_force(i);
        k_r3.col(i) = dt * (initial_velocities.col(i) + 0.5 * k_v2.col(i));
        k_v3.col(i) = dt * (total_force_k3.col(i) / particle_i.return_mass());
    }

    // k4
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        arma::vec position3 = initial_positions.col(i) + k_r3.col(i);
        arma::vec velocity3 = initial_velocities.col(i) + k_v3.col(i);

        particle_i.set_position(position3);
        particle_i.set_velocity(velocity3);
    }

    // Evaluate force again after intermediate state update
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        total_force_k4.col(i) = total_force(i);
        k_r4.col(i) = dt * (initial_velocities.col(i) + k_v3.col(i));
        k_v4.col(i) = dt * (total_force_k4.col(i) / particle_i.return_mass());
    }

    // Final updates
    for(int i = 0; i < n; i++) {
        Particle& particle_i = particle_collection[i];
        arma::vec r_ip1 = initial_positions.col(i) + (1.0 / 6.0) * (k_r1.col(i) + 2 * k_r2.col(i) + 2 * k_r3.col(i) + k_r4.col(i));
        arma::vec v_ip1 = initial_velocities.col(i) + (1.0 / 6.0) * (k_v1.col(i) + 2 * k_v2.col(i) + 2 * k_v3.col(i) + k_v4.col(i));

        particle_i.set_position(r_ip1);
        particle_i.set_velocity(v_ip1);
    }

    simulation_time += dt;
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

void PenningTrap::change_time(double t)
{
	simulation_time = t;
}


















