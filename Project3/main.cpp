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

arma::vec RK4(n, dt){ //Code to evolve RK4 in time using n steps and dt timesteps
    arma::vec pos_RK4(n, arma::fill::none);
    arma::vec vel_RK4(n, arma::fill::none);
    for (int i = 0; i < n; i++) {   //Loop over the chosen n
        trap.evolve_RK4(dt);        //Evolve the system in time
        pos_RK4(i) = trap.return_position;  //Save the positions and velocities
        vel_RK4(i) = trap.return_velocity;
    data = (pos_RK4, vel_RK4);
    return data;
    }
}

int main()
{
    // Define particle 1 and particle 2
    arma::vec position1 = {20, 0, 20};
    arma::vec velocity1 = {0, 25, 0};
    Particle particle1 = Particle(1.0, 40.078, position1, velocity1);

    // std::cout << "charge: " << particle1.return_charge() << std::endl;
    // std::cout << "mass: " << particle1.return_mass() << std::endl;
    // std::cout << "velocity: " << particle1.return_velocity() << std::endl;
    // std::cout << "position: " << particle1.return_position() << std::endl;

    arma::vec position2 = {25, 25, 0};
    arma::vec velocity2 = {0, 40, 5};
    Particle particle2 = Particle(1.0, 40.078, position2, velocity2);

    // std::cout << "Total force particle 1: " << trap.total_force(0) << std::endl;
    // std::cout << "Total force particle 2: " << trap.total_force(1) << std::endl;

    // std::cout << "Total force particle 1 (interactions): " << trap_with_interactions.total_force(0) << std::endl;
    // std::cout << "Total force particle 2 (interactions): " << trap_with_interactions.total_force(1) << std::endl;

    // ---------------  SPECIFIC ANALYTICAL SOLUTION ---------------
    PenningTrap trap;                //Adding the chosen particle(s) without interactions
    trap.add_particle(particle1);
    // trap.add_particle(particle2);

    // PenningTrap trap;
    // trap_with_interactions.add_particle(particle1); //Adding the chosen particle(s) with interactions
    // trap_with_interactions.add_particle(particle2);

	int n1 = 4000; //n values from task 8
    int n2 = 8000;
    int n3 = 16000;
    int n4 = 32000;

    double dt1 = 50 / n1; //Calculate step size to keep total time 50 microseconds
    double dt2 = 50 / n2;
    double dt3 = 50 / n3;
    double dt4 = 50 / n4;

    
    arma::vec z_positions_1(n1); // Initialize time-related variables
    arma::vec times_1(n1);
    // Fill time values
    double time = 0.0; 
    for (int i = 0; i < n1; i++) {
        times_1[i] = time;
        time += dt1;
    }

    arma::vec z_positions_2(n2);
    arma::vec times_2(n2);
    double time = 0.0; 
    for (int i = 0; i < n2; i++) {
        times_2[i] = time;
        time += dt1;
    }

    arma::vec z_positions_1(n3);
    arma::vec times_3(n3);
    double time = 0.0; 
    for (int i = 0; i < n3; i++) {
        times_3[i] = time;
        time += dt3;
    }

    arma::vec z_positions_1(n4);
    arma::vec times_4(n4);
    double time = 0.0; 
    for (int i = 0; i < n4; i++) {
        times_4[i] = time;
        time += dt4;
    }

    // ---------------  SPECIFIC ANALYTICAL SOLUTION z-plane ---------------
    
    // Calculate specific analytical z-positions
    z_positions = trap.specific_analytical_z(particle1, times);

    // Write to file
    std::string filename_z = "specific_analytical_z.txt";
    write_to_file(filename_z, times, z_positions);

    // --------------- SPECIFIC ANALYTICAL SOLUTION (x, y)-plane ---------------

	// ---------- Particle 1 - XY ---------
	arma::vec x1_analytical = arma::vec(times.n_elem);
	arma::vec y1_analytical = arma::vec(times.n_elem);
	std::string filename_xy1 = "specific_analytical_xy_particle1.txt";
	trap.specific_analytical_xy(particle1, times, x1_analytical, y1_analytical);
	write_to_file(filename_xy1, x1_analytical, y1_analytical);


	// ---------- Particle 2 - XY ---------
	arma::vec x2_analytical = arma::vec(times.n_elem);
	arma::vec y2_analytical = arma::vec(times.n_elem);
	std::string filename_xy2 = "specific_analytical_xy_particle2.txt";
	trap.specific_analytical_xy(particle2, times, x2_analytical, y2_analytical);
	write_to_file(filename_xy2, x2_analytical, y2_analytical);

    // --------------- SIMULATING MOVEMENTS OF THE PARTICLES ---------------


	// ---------------RK4 ---------------

    RK4_data1 = RK4(n1, dt1);
    // RK4_data2 = RK4(n2, dt2);
    // RK4_data3 = RK4(n3, dt3);
    // RK4_data4 = RK4(n4, dt4);

	std::string filename_RK4 = "RK4_xy_particle1.txt";  //Save the positions and velocities to file
	write_to_file(filename_RK4, pos_RK4, vel_RK4);

	// --------------- FWD EULER ---------------

	// --------------- RELATIVE ERROR ---------------


    return 0;
}


