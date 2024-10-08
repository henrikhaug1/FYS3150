#include <iostream>
#include <armadillo>
#include "Particle.hpp"
#include "PenningTrap.hpp"

int main()
{
	arma::vec position1 = arma::vec({20, 0, 20});
	arma::vec velocity1 = arma::vec({0, 25, 0});
	Particle particle1 = Particle(1.0, 40.078, position1, velocity1);

	arma::vec position2 = arma::vec({25, 25, 0});
	arma::vec velocity2 = arma::vec({0, 40, 5});
	Particle particle2 = Particle(1.0, 40.078, position2, velocity2);

	std::cout << "mass : " << particle1.mass << " charge: " << particle1.charge << " velocity: "<< particle1.velocity << " position: " << particle1.position << "\n";
	std::cout << "mass : " << particle2.mass << " charge: " << particle2.charge << " velocity: "<< particle2.velocity << " position: " << particle2.position << "\n";
	
	PenningTrap trap = PenningTrap();
	trap.add_particle(particle1);
	trap.add_particle(particle2);

	trap.evolve_forward_Euler(0.01);
	std::cout << particle1.position << " " << particle1.velocity << std::endl;
	std::cout << particle2.position << " " << particle2.velocity << std::endl;

}