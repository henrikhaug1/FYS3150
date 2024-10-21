#include <iostream>
#include <armadillo>
#include <iomanip>
#include <string>
#include <fstream>
#include "Particle.hpp"
#include "PenningTrap.hpp"
#include "main.cpp"

double mass = 40.078;
int charge = 1;
int t_max = 500;
int t = 0;
int n_step = 32000*500/50;
double dt = 500/n_step;

arma::vec f = arma::vec({0.1, 0.4, 0.7});
arma::vec omega_v = linspace(0.2, 2.5, 0.02)

int counter = 0

for(int i = 0; i < f.n_elem; i++)
{
	for(int j = 0; j < omega_v.n_elem; j ++)
	{
		PenningTrap trap = PenningTrap(T, 0.025 * V, 500, false, true, f[i], omega_v[j]);
		trap.add_random_particle(100, charge, mass);

		for(int j = 0; j < n_step; j++)
		{
			trap.evolve_RK4(dt)
		}

		counter += count_particles()

	}




}


