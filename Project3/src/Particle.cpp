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

// Function that returns the charge 
double charge()
{
	return charge;
}


// Function that returns the mass 
double mass()
{
	return mass;
}


// Function that returns the position 
arma::vec position()
{
	return position;
}


// Function that returns the velocity 
arma::vec velocity()
{
	return velocity;
}