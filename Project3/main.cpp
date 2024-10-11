#include <iostream>
#include <armadillo>
#include "Particle.hpp"
#include "PenningTrap.hpp"

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

	//trap.evolve_forward_Euler(0.01);
	//std::cout << particle1.position << " " << particle1.velocity << std::endl;
	//std::cout << particle2.position << " " << particle2.velocity << std::endl;

}