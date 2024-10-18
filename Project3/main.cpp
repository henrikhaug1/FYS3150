#include <iostream>
#include <armadillo>
#include <iomanip>
#include <string>
#include <fstream>
#include "Particle.hpp"
#include "PenningTrap.hpp"

// Function to write data to file
void write_xyz_to_file(std::string filename, arma::vec x, arma::vec y, arma::vec z, arma::vec time)
{
    int width = 30;
    int prec = 15;

    std::ofstream ofile;
    ofile.open(filename);

    ofile << std::scientific << std::setprecision(prec);
    ofile << std::left << std::setw(width) << "time"
                       << std::setw(width) << "x"
                       << std::setw(width) << "y" 
                       << std::setw(width) << "z" << std::endl;

    for (int i = 0; i < x.n_elem; i++) {
        ofile << std::left << std::setw(width) << time[i]
                           << std::setw(width) << x[i]
                           << std::setw(width) << y[i]
                           << std::setw(width) << z[i] << std::endl;
    }

    ofile.close();
}


void RK4(double n, double dt, PenningTrap trap, arma::vec& pos_RK4, arma::vec& vel_RK4, arma::vec& time)
{
    for (int i = 0; i < time.n_elem; i++) {   //Loop over the chosen n
        trap.evolve_RK4(dt);        //Evolve the system in time
        pos_RK4(i) = trap.particle_collection[0].return_position()(0);  //Save the positions and velocities
        vel_RK4(i) = trap.particle_collection[0].return_velocity()(0);
    }
}

arma::vec linspace(double start, double end, double dt)
{
    int n = static_cast<int>((end - start) / dt);
    return arma::linspace(start, end, n); 
}

    

int main(){

    // ---------- Particle 1 ----------
    arma::vec position1 = {20, 0, 20};
    arma::vec velocity1 = {0, 25, 0};
    Particle particle1 = Particle(1.0, 40.078, position1, velocity1);

    // ---------- Particle 2 ----------
    arma::vec position2 = {25, 25, 0};
    arma::vec velocity2 = {0, 40, 5};
    Particle particle2 = Particle(1.0, 40.078, position2, velocity2);

    // Making time 
    double t = 0.0;
    double dt = 1e-3;
    int t_max = 50;
    arma::vec time = arma::vec(t_max/dt + 1);
    for(int i = 0; i < time.n_elem; i++)
    {
        time(i) = t;
        t += dt;
    }

    // ---------------  SPECIFIC ANALYTICAL SOLUTION ---------------

    // ---------- PenningTrap - analytical ----------
    PenningTrap trap_analytical;
    trap_analytical.add_particle(particle1);
    trap_analytical.add_particle(particle2);


    arma::vec x_analytical = arma::vec(time.n_elem);
    arma::vec y_analytical = arma::vec(time.n_elem);
    arma::vec z_analytical = arma::vec(time.n_elem);

    trap_analytical.specific_analytical_solution(particle1, time, x_analytical, y_analytical, z_analytical);
    std::string filename_analytical = "xyz_analytical.txt";
    write_xyz_to_file(filename_analytical, x_analytical, y_analytical, z_analytical, time);


    // ---------------  RK4 ---------------

    // ---------- PenningTrap - RK4 ----------
    PenningTrap trap_RK4;
    trap_RK4.add_particle(particle1);
    trap_RK4.add_particle(particle2);

    arma::vec x_RK4_1 = arma::vec(time.n_elem);
    arma::vec y_RK4_1 = arma::vec(time.n_elem);
    arma::vec z_RK4_1 = arma::vec(time.n_elem);

    arma::vec x_RK4_2 = arma::vec(time.n_elem);
    arma::vec y_RK4_2 = arma::vec(time.n_elem);
    arma::vec z_RK4_2 = arma::vec(time.n_elem);

    arma::vec x_RK4_1_velocity = arma::vec(time.n_elem);
    arma::vec y_RK4_1_velocity = arma::vec(time.n_elem);
    arma::vec z_RK4_1_velocity = arma::vec(time.n_elem);

    arma::vec x_RK4_2_velocity = arma::vec(time.n_elem);
    arma::vec y_RK4_2_velocity = arma::vec(time.n_elem);
    arma::vec z_RK4_2_velocity = arma::vec(time.n_elem);

    for(int i = 0; i < time.n_elem; i++)
    {
        trap_RK4.evolve_RK4(dt);
        x_RK4_1(i) = trap_RK4.particle_collection[0].return_position()(0);
        y_RK4_1(i) = trap_RK4.particle_collection[0].return_position()(1);
        z_RK4_1(i) = trap_RK4.particle_collection[0].return_position()(2);

        x_RK4_2(i) = trap_RK4.particle_collection[1].return_position()(0);
        y_RK4_2(i) = trap_RK4.particle_collection[1].return_position()(1);
        z_RK4_2(i) = trap_RK4.particle_collection[1].return_position()(2);

        x_RK4_1_velocity(i) = trap_RK4.particle_collection[0].return_velocity()(0);
        y_RK4_1_velocity(i) = trap_RK4.particle_collection[0].return_velocity()(1);
        z_RK4_1_velocity(i) = trap_RK4.particle_collection[0].return_velocity()(2);

        x_RK4_2_velocity(i) = trap_RK4.particle_collection[1].return_velocity()(0);
        y_RK4_2_velocity(i) = trap_RK4.particle_collection[1].return_velocity()(1);
        z_RK4_2_velocity(i) = trap_RK4.particle_collection[1].return_velocity()(2);



    }

    std::string filenameRK4_1 = "xyz_RK4_1.txt";
    write_xyz_to_file(filenameRK4_1, x_RK4_1, y_RK4_1, z_RK4_1, time);

    std::string filenameRK4_1_velocity = "xyz_RK4_1_velocity.txt";
    write_xyz_to_file(filenameRK4_1_velocity, x_RK4_1_velocity, y_RK4_1_velocity, z_RK4_1_velocity, time);

    std::string filenameRK4_2 = "xyz_RK4_2.txt";
    write_xyz_to_file(filenameRK4_2, x_RK4_2, y_RK4_2, z_RK4_2, time);

    std::string filenameRK4_2_velocity = "xyz_RK4_2_velocity.txt";
    write_xyz_to_file(filenameRK4_2_velocity, x_RK4_2_velocity, y_RK4_2_velocity, z_RK4_2_velocity, time);



    

    //---------- PenningTrap - RK4 - With interactions----------

    PenningTrap trap_RK4_interactions(T, 0.025 * V, 500, true, false);
    trap_RK4_interactions.add_particle(particle1);
    trap_RK4_interactions.add_particle(particle2);

    arma::vec x_RK4_interactions_1 = arma::vec(time.n_elem);
    arma::vec y_RK4_interactions_1 = arma::vec(time.n_elem);
    arma::vec z_RK4_interactions_1 = arma::vec(time.n_elem);

    arma::vec x_RK4_interactions_2 = arma::vec(time.n_elem);
    arma::vec y_RK4_interactions_2 = arma::vec(time.n_elem);
    arma::vec z_RK4_interactions_2 = arma::vec(time.n_elem);

    arma::vec x_RK4_interactions_1_velocity = arma::vec(time.n_elem);
    arma::vec y_RK4_interactions_1_velocity = arma::vec(time.n_elem);
    arma::vec z_RK4_interactions_1_velocity = arma::vec(time.n_elem);

    arma::vec x_RK4_interactions_2_velocity = arma::vec(time.n_elem);
    arma::vec y_RK4_interactions_2_velocity = arma::vec(time.n_elem);
    arma::vec z_RK4_interactions_2_velocity = arma::vec(time.n_elem);

    for(int i = 0; i < time.n_elem; i++)
    {
        trap_RK4_interactions.evolve_RK4(dt);
        x_RK4_interactions_1(i) = trap_RK4_interactions.particle_collection[0].return_position()(0);
        y_RK4_interactions_1(i) = trap_RK4_interactions.particle_collection[0].return_position()(1);
        z_RK4_interactions_1(i) = trap_RK4_interactions.particle_collection[0].return_position()(2);

        x_RK4_interactions_2(i) = trap_RK4_interactions.particle_collection[1].return_position()(0);
        y_RK4_interactions_2(i) = trap_RK4_interactions.particle_collection[1].return_position()(1);
        z_RK4_interactions_2(i) = trap_RK4_interactions.particle_collection[1].return_position()(2);

        x_RK4_interactions_1_velocity(i) = trap_RK4_interactions.particle_collection[0].return_velocity()(0);
        y_RK4_interactions_1_velocity(i) = trap_RK4_interactions.particle_collection[0].return_velocity()(1);
        z_RK4_interactions_1_velocity(i) = trap_RK4_interactions.particle_collection[0].return_velocity()(2);

        x_RK4_interactions_2_velocity(i) = trap_RK4_interactions.particle_collection[1].return_velocity()(0);
        y_RK4_interactions_2_velocity(i) = trap_RK4_interactions.particle_collection[1].return_velocity()(1);
        z_RK4_interactions_2_velocity(i) = trap_RK4_interactions.particle_collection[1].return_velocity()(2);
    }

    std::string filenameRK4_interactions_1 = "xyz_RK4_interactions_1.txt";
    write_xyz_to_file(filenameRK4_interactions_1, x_RK4_interactions_1, y_RK4_interactions_1, z_RK4_interactions_1, time);

    std::string filenameRK4_interactions_1_velocity = "xyz_RK4_interactions_1_velocity.txt";
    write_xyz_to_file(filenameRK4_interactions_1_velocity, x_RK4_interactions_1_velocity, y_RK4_interactions_1_velocity, z_RK4_interactions_1_velocity, time);


    std::string filenameRK4_interactions_2 = "xyz_RK4_interactions_2.txt";
    write_xyz_to_file(filenameRK4_interactions_2, x_RK4_interactions_2, y_RK4_interactions_2, z_RK4_interactions_2, time);

    std::string filenameRK4_interactions_2_velocity = "xyz_RK4_interactions_2_velocity.txt";
    write_xyz_to_file(filenameRK4_interactions_2_velocity, x_RK4_interactions_2_velocity, y_RK4_interactions_2_velocity, z_RK4_interactions_2_velocity, time);


    // ---------------  FE ---------------

    // ---------- PenningTrap - FE ----------

    PenningTrap trap_FE;
    trap_FE.add_particle(particle1);
    trap_FE.add_particle(particle2);

    arma::vec x_FE = arma::vec(time.n_elem);
    arma::vec y_FE = arma::vec(time.n_elem);
    arma::vec z_FE = arma::vec(time.n_elem);

    for(int i = 0; i < time.n_elem; i++)
    {
        trap_FE.evolve_RK4(dt);
        x_FE(i) = trap_FE.particle_collection[0].return_position()(0);
        y_FE(i) = trap_FE.particle_collection[0].return_position()(1);
        z_FE(i) = trap_FE.particle_collection[0].return_position()(2);
    }

    std::string filenameFE = "xyz_FE.txt";
    write_xyz_to_file(filenameFE, x_FE, y_FE, z_FE, time);


    return 0;
}