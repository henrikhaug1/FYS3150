#include "problem8_functions.hpp"

#include <armadillo>
#include <iostream>
#include <cmath>

arma::vec absolute_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec absolute_error_vec = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		double abs_value = fabs(approx_vec[i] - true_vec[i]);
		absolute_error_vec[i] = fabs(abs_value);
	}

	return absolute_error_vec;
}

arma::vec relative_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec relative_error_vec = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		double rel_value = (approx_vec[i] - true_vec[i]) / true_vec[i];
		relative_error_vec[i] = fabs(rel_value);
	}

	return relative_error_vec;
}




