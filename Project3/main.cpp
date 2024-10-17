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


    PenningTrap trap;
    trap.add_particle(particle1);
    trap.add_particle(particle2);

    std::cout << "Total force particle 1: " << trap.total_force(0) << std::endl;
    std::cout << "Total force particle 2: " << trap.total_force(1) << std::endl;


    bool particle_interactions_in;
    PenningTrap trap_with_interactions(T, 0.25*V, 500, true, false);
    trap_with_interactions.add_particle(particle1);
    trap_with_interactions.add_particle(particle2);

    std::cout << "Total force particle 1 (interactions): " << trap_with_interactions.total_force(0) << std::endl;
    std::cout << "Total force particle 2 (interactions): " << trap_with_interactions.total_force(1) << std::endl;



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

    // --------------- WITHOUT PARTICLE INTERACTION (x, y)-plane ---------------

	// ---------- Particle 1 - XY ---------
	arma::vec x1 = arma::vec(times.n_elem);
	arma::vec y1 = arma::vec(times.n_elem);
	std::string filename_xy1 = "specific_analytical_xy_particle1.txt";
	trap.specific_analytical_xy(particle1, times, x1, y1);
	write_to_file(filename_xy1, x1, y1);


	// ---------- Particle 2 - XY ---------
	arma::vec x2 = arma::vec(times.n_elem);
	arma::vec y2 = arma::vec(times.n_elem);
	std::string filename_xy2 = "specific_analytical_xy_particle2.txt";
	trap.specific_analytical_xy(particle2, times, x2, y2);
	write_to_file(filename_xy2, x2, y2);


	// --------------- WITH INTERACTION (x, y)-plane ---------------

	// ---------- Particle 1 - XY ---------
	arma::vec x1_interaction = arma::vec(times.n_elem);
	arma::vec y1_interaction = arma::vec(times.n_elem);
	std::string filename_xy1_interactions = "specific_analytical_xy_particle1_interactions.txt";
	trap_with_interactions.specific_analytical_xy(particle1, times, x1_interaction, y1_interaction);
	write_to_file(filename_xy1_interactions, x1_interaction, y1_interaction);


	
	// ---------- Particle 2 - XY ---------
	arma::vec x2_interaction = arma::vec(times.n_elem);
	arma::vec y2_interaction = arma::vec(times.n_elem);
	std::string filename_xy2_interactions = "specific_analytical_xy_particle2_interactions.txt";
	trap.specific_analytical_xy(particle2, times, x2_interaction, y2_interaction);
	write_to_file(filename_xy2_interactions, x2_interaction, y2_interaction);

    /*
    // --------------- WITHOUT PARTICLE INTERACTION (x, v_x)-plane ---------------

    // ---------- Particle 1 ---------
    arma::vec x1 = arma::vec(times.n_elem);
    arma::vec v_x1 = arma::vec(times.n_elem);
    std::string filename_xy1 = "specific_analytical_xy_particle1.txt";
    trap.specific_analytical_xy(particle1, times, x1, v_x1);
    write_to_file(filename_xy1, x1, y1);


    // ---------- Particle 2 - XY ---------
    arma::vec x2 = arma::vec(times.n_elem);
    arma::vec v_x2 = arma::vec(times.n_elem);
    std::string filename_xy2 = "specific_analytical_xy_particle2.txt";
    trap.specific_analytical_xy(particle2, times, x2, v_x2);
    write_to_file(filename_xy2, x2, y2);
    */
    return 0;
}


