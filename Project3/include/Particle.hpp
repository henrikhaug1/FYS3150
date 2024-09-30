#ifndef __Particle_hpp__
#define __particle_hpp__

class Particle
{

	public:

		double charge;
		double mass;
		arma::vec position;
		arma::vec velocity;

		//constructor that assigns values to the member variables
		Particle(double charge_in, double mass_in, arma::vec position_in, arma::vec velocity_in);

}

#endif