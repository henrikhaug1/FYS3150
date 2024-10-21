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
	double mass = 40.078;
	int charge = 1;
	int t_max = 500;
	int t = 0;
	int n_step = 40000;
	double dt = 500./n_step;

	arma::vec f = arma::vec({0.1, 0.4, 0.7});
	arma::vec omega_v = linspace(0.2, 2.5, 0.02);

	arma::vec particles_outside_trap = arma::vec(omega_v.n_elem);

	for(int i = 0; i < f.n_elem; i++)
	{
		for(int j = 0; j < omega_v.n_elem; j ++)
		{
			std::cout << "hei" << std::endl;
			PenningTrap trap = PenningTrap(T, 0.025 * V, 500, false, true, f[i], omega_v[j]);
			trap.add_random_particle(100, charge, mass);

			for(int k = 0; k < n_step; k++)
			{
				trap.evolve_RK4(dt);
			}

			particles_outside_trap[j] = trap.count_particles();

		}

		std::string filename_particles_outside = "f" + std::to_string(f[i]) + ".txt";
		write_to_file(filename_particles_outside, particles_outside_trap, omega_v);
}

return 0;
}