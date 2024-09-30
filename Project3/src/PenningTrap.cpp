#include <iostream>
#include <armadillo>
#include "PenningTrap.hpp"

PenningTrap::PenningTrap(arma::vec external_electric_field, arma::vec external_magnetic_field, 
		arma::vec force_interaction)
{
	external_electric_field = external_electric_field_in;
	external_magnetic_field = external_magnetic_field_in;
	force_interaction = froce_interaction_in;

}