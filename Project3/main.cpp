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

// Function to write relative error to file
void write_error_to_file(std::string filename, arma::vec error, arma::vec time)
{
    int width = 30;
    int prec = 15;

    std::ofstream ofile;
    ofile.open(filename);

    ofile << std::scientific << std::setprecision(prec);
    ofile << std::left << std::setw(width) << "time"
                       << std::setw(width) << "relative_error" << std::endl;

    for (int i = 0; i < error.n_elem; i++) {
        ofile << std::left << std::setw(width) << time[i]
                           << std::setw(width) << error[i] << std::endl;
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

arma::vec error_convergence_rate(arma::vec dt, arma::vec delta_max)
{
    arma::vec error_convergence_rate_vec(dt.n_elem);
    error_convergence_rate_vec[0] = 0;


    for(int i = 1; i < dt.n_elem; i++)
    {

        double r_err;
        double delta_max_current = delta_max[i];
        double delta_max_prev = delta_max[i-1];
        double dt_current = dt[i];
        double dt_prev = dt[i-1];

        for(int k = 1; k <= 3; k++)
        {
            r_err += log10(delta_max_current / delta_max_prev) / log10(dt_current / dt_prev);
        }

        error_convergence_rate_vec[i] = (1/3) * r_err;
    }

    return error_convergence_rate_vec;
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
    arma::vec steps = arma::vec({4000, 8000, 16000, 32000});
    double t = 0.0;
    int t_max = 50;
    double dt = t_max/steps[3];
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

    // ---------- PenningTrap - FE Without interactions ----------

    PenningTrap trap_FE;
    trap_FE.add_particle(particle1);
    trap_FE.add_particle(particle2);

    arma::vec x_FE_1 = arma::vec(time.n_elem);
    arma::vec y_FE_1 = arma::vec(time.n_elem);
    arma::vec z_FE_1 = arma::vec(time.n_elem);

    arma::vec x_FE_2 = arma::vec(time.n_elem);
    arma::vec y_FE_2 = arma::vec(time.n_elem);
    arma::vec z_FE_2 = arma::vec(time.n_elem);

    for(int i = 0; i < time.n_elem; i++)
    {
        trap_FE.evolve_RK4(dt);
        x_FE_1(i) = trap_FE.particle_collection[0].return_position()(0);
        y_FE_1(i) = trap_FE.particle_collection[0].return_position()(1);
        z_FE_1(i) = trap_FE.particle_collection[0].return_position()(2);

        x_FE_2(i) = trap_FE.particle_collection[1].return_position()(0);
        y_FE_2(i) = trap_FE.particle_collection[1].return_position()(1);
        z_FE_2(i) = trap_FE.particle_collection[1].return_position()(2);
    }

    std::string filenameFE_1 = "xyz_FE_1.txt";
    write_xyz_to_file(filenameFE_1, x_FE_1, y_FE_1, z_FE_1, time);

    std::string filenameFE_2 = "xyz_FE_2.txt";
    write_xyz_to_file(filenameFE_2, x_FE_2, y_FE_2, z_FE_2, time);

    //---------- PenningTrap - FE With interactions ----------

    PenningTrap trap_FE_interactions(T, 0.025 * V, 500, true, false);
    trap_FE_interactions.add_particle(particle1);
    trap_FE_interactions.add_particle(particle2);

    arma::vec x_FE_1_interactions = arma::vec(time.n_elem);
    arma::vec y_FE_1_interactions = arma::vec(time.n_elem);
    arma::vec z_FE_1_interactions = arma::vec(time.n_elem);

    arma::vec x_FE_2_interactions = arma::vec(time.n_elem);
    arma::vec y_FE_2_interactions = arma::vec(time.n_elem);
    arma::vec z_FE_2_interactions = arma::vec(time.n_elem);

    for(int i = 0; i < time.n_elem; i++)
    {
        trap_FE.evolve_RK4(dt);
        x_FE_1_interactions(i) = trap_FE_interactions.particle_collection[0].return_position()(0);
        y_FE_1_interactions(i) = trap_FE_interactions.particle_collection[0].return_position()(1);
        z_FE_1_interactions(i) = trap_FE_interactions.particle_collection[0].return_position()(2);

        x_FE_2_interactions(i) = trap_FE_interactions.particle_collection[1].return_position()(0);
        y_FE_2_interactions(i) = trap_FE_interactions.particle_collection[1].return_position()(1);
        z_FE_2_interactions(i) = trap_FE_interactions.particle_collection[1].return_position()(2);
    }

    std::string filenameFE_1_interactions = "xyz_FE_1_interactions.txt";
    write_xyz_to_file(filenameFE_1_interactions, x_FE_1_interactions, y_FE_1_interactions, z_FE_1_interactions, time);

    std::string filenameFE_2_interactions = "xyz_FE_2_interactions.txt";
    write_xyz_to_file(filenameFE_2_interactions, x_FE_2_interactions, y_FE_2_interactions, z_FE_2_interactions, time);





    // ---------- Error ----------
    for (int j=0; j < steps.n_elem; j++)
    {
        double dt = 50.0 / steps[j];  
        arma::vec time = arma::linspace(0.0, 50.0, steps[j]);  // Updated time vector with correct size

        // Re-run RK4 and FE with new dt for current step size
        PenningTrap trap_RK4_error, trap_FE_error, trap_analytical_error;
        trap_RK4_error.add_particle(particle1);
        trap_FE_error.add_particle(particle1);
        trap_analytical_error.add_particle(particle1);

        arma::vec x_RK4(time.n_elem);
        arma::vec x_FE(time.n_elem);
        arma::vec x_analytical(time.n_elem);
        arma::vec y_analytical(time.n_elem); 
        arma::vec z_analytical(time.n_elem);
        arma::vec relative_error_RK4(time.n_elem);
        arma::vec relative_error_FE(time.n_elem);

        // Calculate the analytical solution
        trap_analytical_error.specific_analytical_solution(particle1, time, x_analytical, y_analytical, z_analytical);

        // RK4 simulation
        for (int i = 0; i < time.n_elem; i++) {
            trap_RK4_error.evolve_RK4(dt);
            x_RK4(i) = trap_RK4_error.particle_collection[0].return_position()(0);

            // Relative error between analytical and RK4
            relative_error_RK4(i) = std::abs(x_RK4(i) - x_analytical(i)) / std::abs(x_analytical(i));
        }


        // Write RK4 error to file
        std::string filename_error_RK4 = "relative_error_RK4_" + std::to_string(static_cast<int>(steps[j])) + ".txt";
        write_error_to_file(filename_error_RK4, relative_error_RK4, time);



        // Forward Euler simulation
        for (int i = 0; i < time.n_elem; i++) {
            trap_FE_error.evolve_forward_euler(dt);
            x_FE(i) = trap_FE_error.particle_collection[0].return_position()(0);

            // Relative error between analytical and FE
            relative_error_FE(i) = std::abs(x_FE(i) - x_analytical(i)) / std::abs(x_analytical(i));
        }

        // Write FE error to file
        std::string filename_error_FE = "relative_error_FE_" + std::to_string(static_cast<int>(steps[j])) + ".txt";
        write_error_to_file(filename_error_FE, relative_error_FE, time);
    }


    // Error convergence rate

    std::vector<std::string> filenames_FE = {"relative_error_FE_4000.txt", "relative_error_FE_8000.txt", "relative_error_FE_16000.txt", "relative_error_FE_32000.txt"};
    std::vector<std::string> filenames_RK4 = {"relative_error_RK4_4000.txt", "relative_error_RK4_8000.txt", "relative_error_RK4_16000.txt", "relative_error_Rk4_32000.txt"};

    arma::vec delta_max_FE = arma::vec(4);
    arma::vec delta_max_RK4 = arma::vec(4);

    for(int i = 0; i < 1; i++) // filenames_FE.size()
    {
        arma::vec rel_err_FE = arma::vec(time.n_elem);
        arma::vec rel_err_RK4 = arma::vec(time.n_elem);

        // FE
        std::ifstream file_FE(filenames_FE[i]);
        std::string line_FE;
        std::getline(file_FE, line_FE);

        while (std::getline(file_FE, line_FE)) 
        {
            std::istringstream iss(line_FE);
            double first_value, second_value;
            rel_err_FE(i) = second_value;
        }

        file_FE.close();

        // RK4
        std::ifstream file_RK4(filenames_RK4[i]);
        std::string line_RK4;
        std::getline(file_RK4, line_RK4);

        while (std::getline(file_RK4, line_RK4)) 
        {
            std::istringstream iss(line_RK4);
            double first_value, second_value;
            rel_err_RK4(i) = second_value;
        }

        delta_max_FE(i) = arma::max(rel_err_FE);
        delta_max_RK4(i) = arma::max(rel_err_RK4);

        file_RK4.close();

        
        std::cout << filenames_FE[i] << "\n";
        rel_err_FE.print("Relative error FE");
        std::cout << "\n";

        std::cout << filenames_RK4[i] << "\n";
        rel_err_FE.print("Relative error FE");
        std::cout << "\n";
        

    }

    arma::vec dt_rel_err = arma::vec({50./4000., 50./8000., 50./16000., 50./32000.});

    arma::vec error_convergance_rate_RK4 = error_convergence_rate(dt_rel_err, delta_max_RK4);
    arma::vec error_convergance_rate_FE = error_convergence_rate(dt_rel_err, delta_max_FE);



    /*
    delta_max_FE.print("delta max FE");
    std::cout << "\n";
    delta_max_RK4.print("delta max RK4");
    std::cout << "\n";
    dt_rel_err.print("dt relative error");
    std::cout << "\n";
    error_convergance_rate_RK4.print("error_convergance_rate_RK4");
    std::cout << "\n";
    error_convergance_rate_FE.print("error_convergance_rate_FE");
    std::cout << "\n";
    */

    return 0;

}
