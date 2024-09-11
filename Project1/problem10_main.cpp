#include <armadillo>
#include <iostream>
#include <iomanip>
#include "problem7_functions.hpp"
#include "problem9_functions.hpp"
#include "problem10_functions.hpp"

int main(){
	arma::ivec n_steps = arma::ivec("10 100 1000 10000 100000 1000000");

	std::ofstream ofile;
	ofile.open("time_comparison.txt");
	ofile << std::scientific << std::setprecision(15);
	ofile << "n_steps    Time general (s)     Time special (s)" << "\n"; //making header for file

	for(int i = 0; i < n_steps.size(); i++){
		double thomas_general_duration_seconds = timer_general(n_steps[i]);
		double thomas_special_duration_seconds = timer_special(n_steps[i]);
		ofile << n_steps[i] << "     " << thomas_general_duration_seconds << "      " << thomas_special_duration_seconds << "\n";
	}
	return 0;
}
