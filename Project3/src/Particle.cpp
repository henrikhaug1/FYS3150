#include <iostream>
#include <armadillo>
#include <vector>

// Constructor 
Particle::Particle(double charge_in, double mass_in, arma::vec position_in, arma::vec velocity_in)
{
	charge = charge_in;
	mass = mass_in;
	position = position_in;
	velocity = velocity_in;
}