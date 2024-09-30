#ifndef __PenningTrap_hpp__
#define __PenningTrap_hpp__

class PenningTrap
{
	public:
		double B_0;
		double V_0;
		double d;
		std::vector<Particle> particle;

	//Constructor 
	PenningTrap(arma::vec external_electric_field, arma::vec external_magnetic_field, 
		arma::vec force_interaction)
}

#endif