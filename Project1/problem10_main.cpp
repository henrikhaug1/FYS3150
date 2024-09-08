#include <armadillo>
#include <iostream>
#include "problem7_functions.hpp"
#include "problem9_functions.hpp"
#include "problem10_functions.hpp"

int main(){
	arma::ivec n_steps = arma::ivec("10 100 1000");

	std::cout << "n   " <<  "Time general (s)   " << "Time special (s) \n" << std::endl;
	for(int i = 0; i < n_steps.size(); i++){
		double thomas_general_duration_seconds = timer_general(n_steps[i]);
		double thomas_special_duration_seconds = timer_special(n_steps[i]);
		std::cout << n_steps[i] << "     " << thomas_general_duration_seconds << "      " << thomas_special_duration_seconds << "\n";
	}
	return 0;
}
