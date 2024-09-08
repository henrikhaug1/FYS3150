#include "problem8_functions.hpp"
#include <iomanip>
#include <armadillo>



int main(){

	arma::ivec n_step_vec = arma::ivec("10 100 1000");
	double h_min = 1.0e-8;
	double h_max = 1;
	double x = 2.0;

	write_h_absolute_relative(n_step_vec, h_min, h_max, x);

	return 0;

}