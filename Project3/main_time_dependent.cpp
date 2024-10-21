#include <iostream>
#include <armadillo>
#include <iomanip>
#include <string>
#include <fstream>
#include "Particle.hpp"
#include "PenningTrap.hpp"

void write_to_file(std::string filename, arma::vec x, arma::vec y)
{
    int width = 30;
    int prec = 15;

    std::ofstream ofile;
    ofile.open(filename);

    ofile << std::scientific << std::setprecision(prec);
    ofile << std::left << std::setw(width) << "x"
                       << std::setw(width) << "y" << std::endl;

    for (int i = 0; i < x.n_elem; i++) {
        ofile << std::left << std::setw(width) << x[i]
                           << std::setw(width) << y[i] << std::endl;
    }

    ofile.close();
}

arma::vec linspace(double start, double end, double dt)
{
    int n = static_cast<int>((end - start) / dt);
    return arma::linspace(start, end, n); 
}


int main()
{
	// ---------- particles still in trap after 500 microseconds for f = 0.1, 0.4, 0.7----------
/*
	double mass = 40.078;
	int charge = 1;
	int t_max = 500;
	int t = 0;
	int n_step = 40000;
	double dt = 500./n_step;

	arma::vec f = arma::vec({0.1, 0.4, 0.7});
	arma::vec omega_v = linspace(0.2, 2.5, 0.02);

	arma::vec particles_inside_trap = arma::vec(omega_v.n_elem);

	for(int i = 0; i < f.n_elem; i++)
	{
		for(int j = 0; j < omega_v.n_elem; j ++)
		{
			std::cout << "hei " << j << std::endl;
			PenningTrap trap = PenningTrap(T, 0.025 * V, 500, false, true, f[i], omega_v[j]);
			trap.add_random_particle(100, charge, mass);

			for(int k = 0; k < n_step; k++)
			{
				trap.evolve_RK4(dt);
			}

			particles_inside_trap[j] = trap.count_particles();

		}

		std::string filename_particles_inside = "f" + std::to_string(static_cast<double>(f[i])) + ".txt";
		write_to_file(filename_particles_inside, particles_inside_trap, omega_v);

	}
*/
// ---------- fine grained - without columb interactions ----------

	double mass = 40.078;
	int charge = 1;
	int t_max = 500;
	int t = 0;
	int n_step = 40000;
	double dt = 500./n_step;

	arma::vec f = arma::vec({0.7});
	arma::vec omega_v = linspace(0.02, 2.5, 0.02);

	arma::vec particles_inside_trap = arma::vec(omega_v.n_elem);

	for(int i = 0; i < f.n_elem; i++)
	{
		for(int j = 0; j < omega_v.n_elem; j ++)
		{
			std::cout << "hei " << j << std::endl;
			PenningTrap trap = PenningTrap(T, 0.025 * V, 500, false, true, f[i], omega_v[j]);
			trap.add_random_particle(100, charge, mass);

			for(int k = 0; k < n_step; k++)
			{
				trap.evolve_RK4(dt);
			}

			particles_inside_trap[j] = trap.count_particles();

		}

		std::string filename_particles_inside = "f" + std::to_string(static_cast<double>(f[i])) + ".txt";
		write_to_file(filename_particles_inside, particles_inside_trap, omega_v);
	}

return 0;
}