#include "problem8_functions.hpp"
#include <iomanip>
#include <armadillo>



int main(){

	double h_min = 1.0e-8;
	double h_max = 1.0;
	double x = 2.0;

	arma::vec n_step_vec = arma::vec("10 100 1000");
	int len_n = n_step_vec.size();

	for(int i = 0; i < len_n; i++ ){
		write_h_absolute_relative(n_step_vec[i], h_min, h_max, x);
	}


	return 0;

}