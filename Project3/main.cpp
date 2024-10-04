#include <iostream>
#include <armadillo>
#include "Particle.hpp"
#include "PenningTrap.hpp"

int main()
{
	arma::vec position1 = arma::vec({20, 0, 20});
	arma::vec velocity1 = arma::vec({0, 40, 5});
	Particle particle = Particle(1.0, 40.078, position1, velocity1);

	std::cout << "mass : " << particle.mass << " charge: " << particle.charge << " velocity: "<< particle.velocity << "\n";
}