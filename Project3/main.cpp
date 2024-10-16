#include <iostream>
#include <armadillo>
#include <iomanip>
#include <string>
#include <fstream>
#include "Particle.hpp"
#include "PenningTrap.hpp"

// Function to write data to file
void write_to_file(std::string filename, arma::vec vec_x_axis, arma::vec vec_y_axis)
{
    int width = 30;
    int prec = 15;

    std::ofstream ofile;
    ofile.open(filename);

    ofile << std::scientific << std::setprecision(prec);
    ofile << std::left << std::setw(width) << "x-axis" << std::setw(width) << "y-axis" << std::endl;

    for (int i = 0; i < vec_x_axis.size(); i++) {
        ofile << std::left << std::setw(width) << vec_x_axis[i]
                           << std::setw(width) << vec_y_axis[i] << std::endl;
    }

    ofile.close();
}

int main()
{
    // Define particle 1 and particle 2
    arma::vec position1 = {20, 0, 20};
    arma::vec velocity1 = {0, 25, 0};
    Particle particle1 = Particle(1.0, 40.078, position1, velocity1);

    std::cout << "charge: " << particle1.return_charge() << std::endl;
    std::cout << "mass: " << particle1.return_mass() << std::endl;
    std::cout << "velocity: " << particle1.return_velocity() << std::endl;
    std::cout << "position: " << particle1.return_position() << std::endl;

    arma::vec position2 = {25, 25, 0};
    arma::vec velocity2 = {0, 40, 5};
    Particle particle2 = Particle(1.0, 40.078, position2, velocity2);

    // Define a PenningTrap with interactions enabled
    PenningTrap trap(true);
    trap.add_particle(particle1);
    trap.add_particle(particle2);

    // Initialize time-related variables
    double time = 0.0;
    double dt = 1e-6;
    arma::vec z_positions(51);
    arma::vec times(51);

    // Fill time values
    for (int i = 0; i < 51; i++) {
        times[i] = time;
        time += dt;
    }

    // Calculate specific analytical z-positions
    z_positions = trap.specific_analytical_z(particle1, times);

    // Write to file
    std::string filename_z = "specific_analytical_z.txt";
    write_to_file(filename_z, times, z_positions);

	// ---------- Particle 1 - XY ---------
	arma::vec x1 = arma::vec(times.n_elem);
	arma::vec y1 = arma::vec(times.n_elem);
	std::string filename_xy = "specific_analytical_xy_particle1.txt";
	trap.specific_analytical_xy(particle1, times, x1, y1);
	write_to_file(filename_xy, x1, y1);


	// ---------- Particle 2 - XY ---------

	arma::vec x2 = arma::vec(times.n_elem);
	arma::vec y2 = arma::vec(times.n_elem);
	std::string filename_xy_interactions = "specific_analytical_xy_interactions_particle1.txt";
	trap.specific_analytical_xy(particle2, times, x2, y2);

	write_to_file(filename_xy_interactions, x2, y2);

    return 0;
}

/*
int main()
{
	arma::vec position1 = {20, 0, 20};
	arma::vec velocity1 = {0, 25, 0};
	Particle particle1 = Particle(1.0, 40.078, position1, velocity1);

	arma::vec position2 = arma::vec({25, 25, 0});
	arma::vec velocity2 = arma::vec({0, 40, 5});
	Particle particle2 = Particle(1.0, 40.078, position2, velocity2);


	//std::cout << "mass : " << particle1.mass << " charge: " << particle1.charge << " velocity: "<< particle1.velocity << " position: " << particle1.position << "\n";
	//std::cout << "mass : " << particle2.mass << " charge: " << particle2.charge << " velocity: "<< particle2.velocity << " position: " << particle2.position << "\n";
	
	PenningTrap trap = PenningTrap();
	trap.add_particle(particle1);
	trap.add_particle(particle2);
	trap.external_E_field(position1);

	std::cout << "--------- PARTICLE 1 ---------" << std::endl;
	std::cout << "Position: \n";
	position1.print();
	std::cout << "\n";
	std::cout << "Velocity: \n";
	velocity1.print(); 
	std::cout << "\n";
	std::cout << "External electric field: \n" << trap.external_E_field(position1) << std::endl;
	std::cout << "\n";
	std::cout << "External magnetic field: \n" << trap.external_B_field(position1) << std::endl;
	std::cout << "\n";
	std::cout << "Force on particle i from particle j:\n " << trap.force_particle(0, 1) << std::endl;
	std::cout << "\n";
	std::cout << "The total force on particle i from the external fields:\n" << trap.total_force_external(0) << std::endl;
	std::cout << "\n";
	std::cout << "The total force on particle i from the other particles:\n " << trap.total_force_particles(0) << std::endl;
	std::cout << "\n";
	std::cout << "The total force on particle i from the other particles and fields:\n " << trap.total_force(0) << std::endl;
	std::cout << "\n";

	
	std::cout << "---------- Forward Euler Particle 1 ----------" << "\n";
	trap.evolve_forward_euler(1e-6);
	std::cout << "Particle1 position after FE1: \n" << trap.particle_collection[0].return_position() << std::endl;
	std::cout << "Particle1 velocity after FE1: \n" << trap.particle_collection[0].return_velocity() << std::endl;
	
	std::cout << "---------- RK4 Particle 1 ----------" << "\n";
	trap.evolve_RK4(1e-6);
	std::cout << "Particle1 position after RK4: \n" << trap.particle_collection[0].return_position() << std::endl;
	std::cout << "Particle1 velocity after RK4: \n" << trap.particle_collection[0].return_velocity() << std::endl;
	



	arma::vec initial_positions = arma::vec(trap.particle_collection.size())
	for(int i = 0; i < trap.particle_collection.size(); i++)
	{
		initial_positions.pushback(trap.particle_collection[i].return_position());
	}

	double time = 0.0;
	double dt = 1e-6;
	std::vector<double> z_positions;
	std::vector<double> times;

	std::ofstream outfile("simulation_data_1_particle.txt");
	outfile << std::scientific << std::setprecision(10);

	for (int i = 0; i < 5000; i++) {
	    trap.evolve_RK4(dt);
	    double z = trap.particle_collection[0].return_position()(2);  // Assuming this method exists
        z_positions.push_back(z);
	    times.push_back(time);

	    outfile << time << "\t" << z << "\n";

	    time += dt;
	}

	outfile.close();

	double charge = trap.particle_collection[0].return_charge();

	double left = (charge * trap.B0 * trap.B0)/trap.particle_collection[0].return_mass();
	double right = 4 * trap.V0 / (trap.d * trap.d);

	//if left < right, the particle stays in penning trap.
	//if left > right, particle flies out and we get unwanted results.
	std::cout << "left: " << left << " right: " << right << std::endl; 
	return 0;
}


*/



